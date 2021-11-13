from cs50 import get_string
import re


def main():

    text = get_string("Text: ")

    letters = 0
    for letter in text:
        if letter.isalpha():
            letters += 1

    # Number of words in text
    words = len(text.split())

    # L is the average number of letters per 100 words in the text
    L = (letters / words) * 100

    # S is the average number of sentences per 100 words in the text
    sentences = len(re.split("[!.?] ", text))
    S = (sentences / words) * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    # Print grade
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")
    

if __name__ == "__main__":
    main()