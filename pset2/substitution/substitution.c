#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool check_alpha(string key);
bool check_multiple(string key);
void calculate_cipher(char character, string key, int capitalization);

// Main takes in an integer as input and an array of string
int main(int argc, string argv[])
{
    // If number of arguments is 2 and input is numbers, reject input and end program
    if (argc != 2 || check_alpha(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;  
    }

    if (check_multiple(argv[1]) == false)
    {
        printf("Key contains multiples\n");
        return 1;
    }
    
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
                // CHANGE
                calculate_cipher(plaintext[i], key, 96);
            }
            else 
            {   
                // CHANGE
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

// Check if the command line argument is alphabetic
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

bool check_multiple(string key)
{
    int i, j;
    int n = strlen(key);

    // check each character in key
    // compare each letter to the others
    for (i = 0; i < n; i ++)
    {
        for (j = 0; j < i; j++)
        {
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
    int alpha = character - capitalization;

    int x = alpha - 1;
    char cipher_character = key[x];

    if (isupper(cipher_character) && islower(character))
    {
        char lower = tolower(cipher_character);
        printf("%c", lower);
    }
    else if (islower(cipher_character) && isupper(character))
    {
        char upper = toupper(cipher_character);
        printf("%c", upper);
    }
    else 
    {
        printf("%c", cipher_character);
    }

    

}