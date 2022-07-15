# Main
def main():
    text = input("Text: ")

    # Count everything up
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Enumerate average
    avg_L = avg(letters, words)
    avg_S = avg(sentences, words)

    # Enumerate grade
    index = (0.0588 * avg_L) - (0.296 * avg_S) - 15.8
    grade = round(index)

    # Output
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(grade))


# Count letters in text
def count_letters(s):
    result = 0
    for letter in s:
        if letter.isalpha():
            result += 1
    return result


# Count words in text
def count_words(s):
    result = 1
    before = ' '
    after = ' '
    for i in range(0, len(s)-1):
        after = s[i + 1]
        if (s[i] == ' ' and (after.isalpha() or before.isalpha())):
            result += 1
        before = s[i]
    return result


# Count sentences in text
def count_sentences(s):
    result = 0
    for i in range(0, len(s)):
        if (s[i] == '.' or s[i] == '!' or s[i] == '?'):
            result += 1
    return result


# Simple average function
def avg(x, y):
    result = x * 100
    result /= y
    return result


if __name__ == "__main__":
    main()