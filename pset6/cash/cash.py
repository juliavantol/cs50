from cs50 import get_float
import math

coins = 0


def main():

    # Prompt for input
    while True:
        change = get_float("Change owed: ")
        if change > 0.0:
            break

    # Quarters
    remainder = calculate_coins(change, 0.25)

    # Dimes
    remainder1 = calculate_coins(remainder, 0.10)

    # Nickels
    remainder2 = calculate_coins(remainder1, 0.05)

    # Pennies
    remainder3 = calculate_coins(remainder2, 0.01)

    print(coins)


def calculate_coins(change, coin):

    global coins
    remainder = round(change % coin, 2)
    used = change - remainder
    coins += round(used / coin)

    return remainder


if __name__ == "__main__":
    main()

