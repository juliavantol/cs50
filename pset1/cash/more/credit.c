#include <stdio.h>
#include <cs50.h>
#include <math.h>

int first_digits(long card_number);

int main(void)

{
    while (true) 
    {

    
        long creditcard_number = get_long("Number: ");

        // find first two digits
        long first_two_digits = first_digits(creditcard_number);
        // all the other numbers
        long number_card = creditcard_number;
        long last_number = 0;
        int test_sum = 0;
        for (int o = 0; number_card > 0; o++)
        {
            // find last digit
            last_number = number_card % 10;
            test_sum = test_sum + last_number;
            // cut last digit off
            number_card = number_card / 10;
            number_card = number_card / 10;
    
        }

        // check sum
        long card_number = creditcard_number;
        int j = 0;
        long second_last_number = 0;
        long last_multiplied = 0;


        long total_sum = 0;
        for (j = 0; card_number > 0; j++) 
        {
        
            // cut last digit off
            card_number = card_number / 10;
            // find last digit
            second_last_number = card_number % 10;
            // cut last digit off
            card_number = card_number / 10;
            last_multiplied = second_last_number * 2;

            for (int x = 0; last_multiplied  > 0; x++)
            {
                // find last digit
                second_last_number = last_multiplied  % 10;
                total_sum = total_sum + second_last_number;
                // cut last digit off
                last_multiplied  = last_multiplied  / 10;

            }


        }

        int final_sum = total_sum + test_sum;
        if (final_sum % 10 != 0 )
        {
            printf("INVALID\n");
            break;
        }

        // calculate length of number
        long length_number = creditcard_number;
        int i = 0;
        for (i = 0; length_number > 0; i++) 
        {
            length_number = length_number / 10;

        }

        length_number = i;
        // printf("sum: %i and length: %li", final_sum, length_number);
        // american express 15 digits starting with 34 or 37
        if (length_number == 15) 
        {   
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                printf("AMEX\n");
                break;

            } 
     
        }

        // mastercard 16 digits starting 51 52 53 54 or 55
        if (length_number == 16) 
        {
            if (first_two_digits > 50 && first_two_digits < 56)
            {
                printf("MASTERCARD\n");
                break;
            }

        }


        int first_digit  = first_two_digits  / 10;

        // visa 13 16 digits starting with 4
        if (length_number == 13 && first_digit == 4)
        {
            printf("VISA\n");
            break;
        }


        else if (length_number == 16 && first_digit == 4)
        {
            printf("VISA\n");
            break;
        }    

      
    printf("INVALID\n");
    break;

    }

    
}

int first_digits(long card_number)
{

    // find first two digits
    long first_two_digits = card_number;
    while (first_two_digits >= 100) 
    {
        first_two_digits /= 10;
    }
    return first_two_digits;
}
