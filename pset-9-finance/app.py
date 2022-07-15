import os

import re # Regular expression operations - src: Lib/re.py

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    data = []
    row = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

    # db error - user not found, unlikely to happen
    if len(row) <= 0:
        return apology("you are not found :O", 400)
    cash = row[0]["cash"]

    row = db.execute("SELECT SUM(shares) AS shares, symbol FROM transactions WHERE user_id=? GROUP BY symbol ORDER BY SUM(shares) DESC", session["user_id"])

    # Create data array of dictionaries
    in_stock = 0
    if len(row) > 0:
        for r in row:
            if int(r['shares']) > 0:
                t = lookup(r["symbol"])
                in_stock += (int(r['shares']) * float(t['price']))
                data.append({"symbol": r['symbol'], "shares": float(r['shares']), "value": usd(t['price']), "name": t['name'], "holding": usd(float(r['shares']) * float(t['price']))})

    cash_total = cash + in_stock
    return render_template("index.html", cash=usd(cash), cash_stock=usd(in_stock), total=usd(cash_total), data=data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Ensure shares are positive int
        try:
            shares = int(request.form.get("shares").replace(",", "."))
            if shares < 0:
                return apology("must give a positive number", 400)
        except ValueError:
            return apology("must give a !number! of shares", 400)

        if not request.form.get("symbol"):
            return apology("must give a stock symbol", 400)

        symDict = lookup(request.form.get("symbol"))

        if symDict == None:
            return apology("symbol not found", 400)

        user_id = session["user_id"]
        real_price = float(symDict["price"]) * shares
        row = db.execute("SELECT cash FROM users WHERE id=?", user_id)

        if len(row) <= 0:
            return apology("you are not found :O", 400)

        user_cash = row[0]["cash"]
        if not float(user_cash) >= real_price:
            return apology("you don't have enaught money", 400)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, value_one) VALUES (?, ?, ?, ?)", user_id, symDict["symbol"], shares, symDict["price"])
        db.execute("UPDATE users SET cash=? WHERE id=?", (user_cash - real_price), user_id)

        # Bought successfuly
        return render_template("bought.html", name=symDict["name"], price=usd(real_price), symbol=symDict["symbol"], shares=shares, usd_left=usd(user_cash - real_price))

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = []
    row = db.execute("SELECT * FROM transactions WHERE user_id=? ORDER BY date", session['user_id'])

    # Check transaction type
    for r in row:
        if r['shares'] > 0:
            t = "Bought"
        elif r['shares'] < 0:
            t = "Sold"
            r['shares'] *= -1
        else:
            # Don't print when shares = 0 - unlikely to happen
            continue

        data.append({"type": t, "symbol": r['symbol'], "shares": r['shares'], "value": usd(float(r['value_one']) * float(r['shares']))})

    return render_template("history.html", data=data)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must give a stock symbol", 400)
        symDict = lookup(request.form.get("symbol"))
        if symDict == None:
            return apology("symbol not found", 400)

        # Quote success
        return render_template("quoted.html", name=symDict["name"], price=usd(symDict["price"]), symbol=symDict["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure passwords were submitted and they are identical
        if not request.form.get("password"):
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must provide your password confirmation", 400)

        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords are different", 400)

        # Additional validation checks

        password = request.form.get("password")

        if len(password) < 8:
            return apology("password must contain at least 8 characters", 400)

        if not re.search("[a-z]", password):
            return apology("password must include lowercase letters", 400)

        if not re.search("[A-Z]", password):
            return apology("password must include uppercase letters", 400)

        if not re.search("[0-9]", password):
            return apology("password must include digits", 400)

        if not re.search("[+\-*\/!()$^]", password):
           return apology("password must include special characters", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exists
        if len(rows) > 0:
            return apology("username already exists", 400)

        # Add account and log in
        password_hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users ('username', 'hash') VALUES (?, ?)", request.form.get("username"), password_hash)
        rows = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            session["user_id"] = rows[0]["id"]
        else:
            return apology("server site problem. email our support.", 500)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Ensure symbol was submitted
        try:
            shares = int(request.form.get("shares").replace(",", "."))
        except ValueError:
            return apology("must give a !number! of shares", 400)

        row = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE symbol=? AND user_id=?", request.form.get("symbol"), session['user_id'])

        if len(row) < 1:
            return apology("you dont have any of this", 400)

        if not shares > row[0]['shares']:

            sym = lookup(request.form.get("symbol"))
            cash = float(db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])[0]['cash'])
            add_cash = float(sym['price']) * shares

            db.execute("INSERT INTO transactions (user_id, symbol, shares, value_one) VALUES (?, ?, ?, ?)", session['user_id'], sym['symbol'], shares * -1, sym['price'])
            db.execute("UPDATE users SET cash=? WHERE id=?", cash + add_cash, session['user_id'])

            return render_template("sold.html", name=sym["name"], symbol=sym["symbol"], shares=shares, price=usd(add_cash), usd_left=usd(cash + add_cash))

        return apology("don't have enaught", 400)

    else:
        owning_sym = []

        row = db.execute("SELECT SUM(shares) AS shares, symbol FROM transactions WHERE user_id=? GROUP BY symbol", session['user_id'])

        if len(row) > 0:
            for r in row:
                if int(r['shares']) > 0:
                    owning_sym.append({"symbol": r['symbol'], "shares": int(r['shares'])})
            if len(owning_sym) > 0:
                return render_template("sell.html", data=owning_sym)

        return apology("nothing to sell", 400)
