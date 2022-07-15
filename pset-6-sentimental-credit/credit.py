# Check if card no. is valid

def is_valid(number):
    to_A = False
    sumA = 0
    sumB = 0
    while (number > 0):
        digit = number % 10
        number //= 10
        if (to_A):
            digit *= 2
            # 2 * something bigger than 4 would create a 2-digit number
            if (digit > 9):
                tmp = digit % 10
                digit //= 10
                digit += tmp
            sumA += digit
            to_A = False
        else:
            sumB += digit
            to_A = True
    # Checksum
    if (((sumA + sumB) % 10) == 0):
        return True
    return False


# Check for name

def name(number):
    if (number >= (34 * (10 ** 13)) and number < (35 * (10 ** 13))):
        return "AMEX"
    elif (number >= (37 * (10 ** 13)) and number < (38 * (10 ** 13))):
        return "AMEX"
    elif (number >= (51 * (10 ** 14)) and number < (56 * (10 ** 14))):
        return "MASTERCARD"
    elif (number >= (4 * (10 ** 15)) and number < (5 * (10 ** 15))):
        return "VISA"
    elif (number >= (4 * (10 ** 12)) and number < (5 * (10 ** 12))):
        return "VISA"
    return "n"


# Get user input (must be a number)

def get_int():
    try:
        num = int(input("Number: "))
    except ValueError:
        return get_int()
    return num


# Main

card_number = get_int()
if (is_valid(card_number) and name(card_number) != "n"):
    print(name(card_number))
else:
    print("INVALID")