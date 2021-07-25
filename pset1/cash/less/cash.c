#include <stdio.h>
#include <cs50.h>
#include <math.h>

void calculate_coins(int currency_coin, int *money_left, int *coins);

int main(void) 

{   
    // ask user for amount of change owed
    float change;
    do 
    {

        change = get_float("Change owed: ");

    }
    while (change <= 0.00);

    // convert dollars to cents
    int money_left = round(change * 100);
    int coins_used = 0;

    // loop until all coins are used and stop if the amount left is 0
    while (true) 
    {

        // quarters
        calculate_coins(25, &money_left, &coins_used);
  
        if (money_left == 0) 
        {
            break;
        }

        // dimes
        calculate_coins(10, &money_left, &coins_used);

        if (money_left == 0) 
        {
            break;
        }

        // nickels
        calculate_coins(5, &money_left, &coins_used);

        if (money_left == 0) 
        {
            break;
        }

        // pennies
        calculate_coins(1, &money_left, &coins_used);

    }

    printf("%i\n", coins_used);

}

// function to calculate amount of coins used and how much money remains
void calculate_coins(int currency_coin, int *money_left, int *coins) 
{
    // use modulo to calculate the remainder of a coin division
    int remainder = *money_left % currency_coin;
    // the sum of money that can be divided solely through the coin
    int sum = *money_left - remainder;
    // how many coins were used
    *coins = *coins + (sum / currency_coin);
    *money_left = *money_left - sum;

}