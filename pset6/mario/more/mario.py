from cs50 import get_int

# Prompt for height until requirements are met
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# Iterate over rows
for row in range(height):

    # Left pyramid
    for left_space in range((height - 1) - row):
        print(" ", end="")

    for left_hash in range(row + 1):
        print("#", end="")

    # Gap
    print("  ", end="")

    # Right pyramid
    for right_hash in range(row + 1):
        print("#", end="")

    hashes = height - row
    for right_space in range(hashes):
        print("", end="")

    # New line
    print()