# Print layers from top to bottom recursively

def print_layer(size, spaces=0):
    if (size > 1):
        print_layer(size - 1, spaces + 1)
    string = ""
    for i in range(0, spaces):
        string += ' '
    for i in range(0, size):
        string += '#'
    print(string + "  " + string[::-1].split(' ')[0])


# Get a valid intiger from user input

def get_int():
    try:
        num = int(input("Height: "))
    except ValueError:
        return get_int()
    if (num >= 1 and num <= 8):
        return num
    else:
        return get_int()


# Main

n = get_int()
print_layer(n)