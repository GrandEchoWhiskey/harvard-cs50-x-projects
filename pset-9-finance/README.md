[<- Back to course](../README.md)

<p align="center"><a href="https://cs50.harvard.edu/x/2022">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/course/harvard100.png" /><br>
</a></p>
<h1 align="center">CS50's Introduction to Computing Science<br><br>Finance</h1>

<p align="center"><a href="#">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/programming/python.png" />
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/programming/html.png" />
</a></p>

### Description:
C$50 Finance, a web app via which you can manage portfolios of stocks. Not only will this tool allow you to check real stocks’ actual prices and portfolios’ values, it will also let you buy (okay, “buy”) and sell (okay, “sell”) stocks by querying IEX for stocks’ prices.

### Configure:
- Visit [iexcloud.io/cloud-login#/register](https://iexcloud.io/cloud-login#/register).
- Select the “Individual” account type, then enter your name, email address, and a password, and click “Create account”.
- Once registered, scroll down to “Get started for free” and click “Select Start plan” to choose the free plan.
- Once you’ve confirmed your account via a confirmation email, visit [iexcloud.io/console/tokens](https://iexcloud.io/console/tokens).
- Copy the key that appears under the Token column (it should begin with pk_).
- In your terminal window, execute:
```
export API_KEY=value
```

### Getting Started:
Export this directory using SVN.
```
svn export https://github.com/GrandEchoWhiskey/harvard-cs50-x-projects/trunk/pset-9-finance
```
Change directory
```
cd pset-9-finance
```
Run flask
```
flask run
```
Open browser and type in your flask server IP Address
