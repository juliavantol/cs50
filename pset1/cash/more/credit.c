#include <stdio.h>
#include <cs50.h>

int main(void)

{
    while (true) 
    {
        long creditcard_number = get_long("Number: ");
        long first_two_digits = creditcard_number;

        while (first_two_digits >= 100) 
        {
            first_two_digits /= 10;
        }
    
        // calculate sum of numbers that don't have to be multiplied
        // copy creditcard number in new variable
        long number_card = creditcard_number;
        int last_number = 0;
        int first_sum = 0;
        for (int o = 0; number_card > 0; o++)
        {
            // find last digit
            last_number = number_card % 10;
            first_sum = first_sum + last_number;
            // cut last digit off
            number_card = number_card / 10;
            number_card = number_card / 10;
    
        }

        // Luhn’s algorithm
        // copy creditcard number in new variable
        long card_number = creditcard_number, total_sum = 0;
        int j; 
        long second_last_number = 0, last_multiplied = 0;

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

        // if the final sum doesn't end in 0, end the program
        int final_sum = total_sum + first_sum;
        if (final_sum % 10 != 0)
        {
            printf("INVALID\n");
            break;
        }

        // calculate length of creditcard number by keeping count how long
        // it takes to reach 0 when deleting the last digit 1 by 1
        long length_number = creditcard_number; 
        int count;
        for (count = 0; length_number > 0; count++) 
        {
            length_number = length_number / 10;
        }

        length_number = count;

        // check for american express if number has 15 digits
        if (length_number == 15) 
        {   
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                printf("AMEX\n");
                break;
            } 
        }

        // check for mastercard if number has 16 digits
        if (length_number == 16) 
        {
            if (first_two_digits > 50 && first_two_digits < 56)
            {
                printf("MASTERCARD\n");
                break;
            }

        }

        // check for visa - has only one standard beginning digit so
        // substract one from the digits variable
        int first_digit  = first_two_digits  / 10;
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

    
        // if nothing matched, declare invalid and end program
        printf("INVALID\n");
        break;
    }
    
}