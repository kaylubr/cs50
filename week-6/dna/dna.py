import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: filename database sequence")
        sys.exit(1)

    # TODO: Read database file into a variable
    list = []
    with open(sys.argv[1]) as database_file:
        database = csv.DictReader(database_file)
        for person in database:
            list.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        sequence = sequence_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    sequences = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
    results = {}  # Contains the STR's sequence from the sequence file

    for seq in sequences:
        results[seq] = longest_match(sequence, seq)

    found = False
    counter = 0

    for person in list:
        for key, val in person.items():
            if counter == 0:
                counter += 1
                continue

            if int(val) != results[key]:
                found = False
                break

            found = True

        counter = 0
        if found:
            print(person['name'])
            break
    else:
        print("No Match.")

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
