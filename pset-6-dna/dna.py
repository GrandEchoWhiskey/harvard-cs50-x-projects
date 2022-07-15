import csv
import sys


def main():

    database = []
    headers = []
    longest_m = []
    sequence = ""

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCES")

    # Read database file into a variable
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        headers = reader.fieldnames
        for person in reader:
            database.append(person)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        sequence = file.readline()

    # Find longest match of each STR in DNA sequence
    for i in range(1, len(headers)):
        longest_m.append(longest_match(sequence, headers[i]))

    # Check database for matching profiles
    for person in database:
        match = []
        for i in range(1, len(headers)):
            if int(person[headers[i]]) == int(longest_m[i-1]):
                match.append(True)
            else:
                match.append(False)
        mat = True
        for m in match:
            mat = mat and m
        if mat:
            print(person[headers[0]])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
