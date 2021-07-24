#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 

{   
    // Ask user for amount of change owed
    float change;
    do {

        change = get_float("Change owed: ");

    }
    while (change <= 0.00);

    // Convert dollars to cents
    int total_amount = round(change * 100);
    int coins = 0;

    // quarters 25
    int quarters;

    // dimes 10
    int dimes;

    // nickels 5
    int nickels;

    // pennies 1
    int pennies;
    

}