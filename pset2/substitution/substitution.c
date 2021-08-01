#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool check_alpha(string key);
bool check_duplicates(string key);
void calculate_cipher(char character, string key, int capitalization);

// Main takes in an integer as input and an array of string
int main(int argc, string argv[])
{
    // If number of arguments is 2 and input is numbers, reject input and end program
    if (argc != 2)
    {
        printf("Usage: ./caesar key.\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;  
    }

    if (check_duplicates(argv[1]) == false)
    {
        printf("Key contains repeated characters.\n");
        return 1;
    }
    if (check_alpha(argv[1]) == false)
    {
        printf("Please only use alphabetical characters.\n");
        return 1;
    }
    
    // Put input into key variable
    string key = argv[1];
    
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

// Check if the key is alphabetic
bool check_alpha(string key)
{
    int i, n;
    char characters[n];
    for (i = 0, n = strlen(key); i < n; i++)
    {
        // As soon as a character is not a digit, return the function as false to reject the input
        if (isalpha(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}

// Check if there are repeated characters in key
bool check_duplicates(string key)
{
    int i, j;
    int n = strlen(key);
    // Compare each letter of the key to the others
    for (i = 0; i < n; i ++)
    {
        for (j = 0; j < i; j++)
        {
            // If a duplicate is found, return false and reject input
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}

// Calculate the cipher character
void calculate_cipher(char character, string key, int capitalization)
{
    // Convert to alphabetical value by subtracting 97 or 64, depending on lowercase/uppercase
    int alpha = (character - capitalization) - 1;
    char cipher_character = key[alpha];

    // Keep the capitalisation of plaintext character intact
    if (isupper(cipher_character) && islower(character))
    {
        printf("%c", tolower(cipher_character));
    }
    else if (islower(cipher_character) && isupper(character))
    {
        printf("%c", toupper(cipher_character));
    }
    else 
    {
        printf("%c", cipher_character);
    }
}