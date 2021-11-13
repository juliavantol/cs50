from sys import argv
import csv
import pandas
import copy


def main():

    if len(argv) != 3:
        print("Usage: python3 dna.py file.csv file.txt")
        sys.exit(0)

    DNA_sequence = []
    headers = []
    dnas = []

    # Save all the column headers in a list
    file = pandas.read_csv(f"{argv[1]}")
    for col in file.columns:
        headers.append(col)

    # Cut the name variable from the list so it's just the SRTs
    STRS = headers[1:]

    # Load CSV file into a dict with all the people's dna sequences
    with open(f"{argv[1]}", "r") as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            dnas.append(row)

    # Load text file into a list
    with open(f"{argv[2]}", "r") as text_file:
        reader = csv.reader(text_file)
        for line in reader:
            DNA_sequence = line

    sequence = {}

    # Count the longest streak of each STR
    for STR in STRS:
        occurences = compare(DNA_sequence[0], STR)
        sequence[STR] = str(occurences)

    # Compare each person's dict of DNA sequences to the dict we are looking for to match
    for person in dnas:
        tmp_person = copy.copy(person)
        tmp_person.pop("name")

        if tmp_person == sequence:
            print(person["name"])
            quit()

    print("No match")


# Search for the longest repeating STR sequence in the entire sequence
def compare(DNA_sequence, STR):

    longest_streak = 0
    current_streak = 0
    i = 0
    j = len(STR)

    # Check if the string of STR length matches the STR we are looking for
    while True:
        string = DNA_sequence[i:j]
        # If it matches, update the streak and move to look to the next STR
        if string == STR:
            current_streak += 1
            i += len(STR)
            j += len(STR)
        # Else, set the streak back to 0 and look at the next character
        else:
            if current_streak > longest_streak:
                longest_streak = current_streak
            current_streak = 0
            i += 1
            j += 1

        if j > len(DNA_sequence):
            if current_streak > longest_streak:
                longest_streak = current_streak
            break

    return longest_streak


if __name__ == "__main__":
    main()
