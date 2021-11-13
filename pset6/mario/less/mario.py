from cs50 import get_int

# Ask for height until requirements are met
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# For every row
for row in range(height):

    # Print hashes
    for space in range((height - 1) - row):
        print(" ", end="")

    # Print crosses
    for hash in range(row + 1):
        print("#", end="")

    # New line
    print()