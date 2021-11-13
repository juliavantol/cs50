from cs50 import get_int
from cs50 import get_string
import math

AMEX = [34, 37]
MASTERCARD = [51, 52, 53, 54, 55]
VISA = [4]
ACCEPTABLE_LENGTHS = [13, 15, 16]


def main():

    # Prompt for input
    number = get_string("Number: ")
    if len(number) not in ACCEPTABLE_LENGTHS:
        print("INVALID")
        quit()

    # Check which card it is by looking at the starting numbers
    card = valid_start(number)

    # End the program if the card doesn't have a valid start
    if card is False:
        print("INVALID")
        quit()

    # Run Luhn's algorithm
    if validity(number) is False:
        print("INVALID")
        quit()
    else:
        print(card)


# Method to check if the card's first numbers are valid starting numbers
def valid_start(number):

    # Putting the starting digits into one string
    start = int(number[:2])

    # Check which brand they belong to
    if start in AMEX:
        return "AMEX"
    elif start in MASTERCARD:
        return "MASTERCARD"
    elif int(number[0]) in VISA:
        return "VISA"

    # Return false if it hasn't been found
    return False


def validity(number):

    i = len(number) - 2
    j = len(number) - 1
    sum = 0

    # Look at every other word starting from the second to last
    while True:
        # Add each digit to the sum
        for digit in str(2 * int(number[i])):
            sum += int(digit)

        i -= 2
        if i < 0:
            break

    # Look at every other word starting from the end
    while True:
        sum += int(number[j])
        j -= 2
        if j < 0:
            break

    # Check if the last digit is equal to 0
    last_digit = (str(sum))[-1]
    if int(last_digit) == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()

