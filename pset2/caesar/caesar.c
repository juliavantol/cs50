#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool check_digit(string key);
void calculate_cipher(char character, int key, int capitalization);

// Main takes in an integer as input and an array of string
int main(int argc, string argv[])
{
    // If number of arguments is 2 and input is numbers, reject input and end program
    if (argc != 2 || check_digit(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Store key into an integer
    int key = atoi(argv[1]);

    // Ask input
    string plaintext = get_string("plaintext: ");

    int i, j, n;
    char x;
    printf("ciphertext: ");
    // Loop through the plaintext character by character
    for (i = 0, j = 0, n = strlen(plaintext); i < n; i++)
    {   
        // If the character is not alphabetical, just print it without doing anything
        if (isalpha(plaintext[i]))
        {
            // If character is lowercase, ASCII value to go to 0 is 96. 
            // If uppercase the ASCII value to go to 0 is 64
            if (islower(plaintext[i]))
            {
                calculate_cipher(plaintext[i], key, 96);
            }
            else 
            {
                calculate_cipher(plaintext[i], key, 64);
            }
        }
        else 
        {
            printf("%c", plaintext[i]);

        }
    }
    printf("\n");
}

// Check if the command line argument is a digit
bool check_digit(string key)
{
    int i, n;
    for (i = 0, n = strlen(key); i < n; i++)
    {
        // As soon as a character is not a digit, return the function as false to reject the input
        if (isdigit(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

// Calculate the cipher character
void calculate_cipher(char character, int key, int capitalization)
{
    // Convert to alphabetical value by subtracting 97 or 64, depending on lowercase/uppercase
    int alpha = character - capitalization;
    // Shift places x times 
    int new_alpha = (alpha + key) % 26;
    // Convert back to ascii
    int ascii = new_alpha + capitalization;
    printf("%c", ascii);
}