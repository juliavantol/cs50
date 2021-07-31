#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

bool check_digit(string key);

// Main takes in an integer as input and an array of string
int main (int argc, string argv[])
{
    // If number of arguments is 2 and input is numbers
    if (argc != 2 || check_digit(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Store key into an integer
    int key = atoi(argv[1]);

    // Ask input
    string plaintext = get_string("plaintext: ");

    // ci = (pi + k) % 26
    int i, j;
    int n = strlen(plaintext);
    // string ciphertext[]; 
    char x;
    for (i = 0, j = 0; i < n; i++)
    {
        x = plaintext[i] + key;
        printf("%c", x);
    }
    printf("\n");

}

// Check if the command line argument is a digit
bool check_digit(string key)
{
    int i;
    int n = strlen(key);
    for (i = 0; i < n; i++)
    {
        if (isdigit(key[i]) == false)
        {
            return false;
        }
    }
    return true;
}