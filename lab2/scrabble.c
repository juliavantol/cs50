#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Compare scores and print winner
    if (score1 > score2) 
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    
}

int compute_score(string word)
{
    // Compute and return score for string
    // The ASCII value of the lowercase alphabet is from 97 to 122. 
    // Alphabetical value is therefore x - 97
    int letter, n;
    int score = 0;

    // Convert each character to lowercase
    // If the character is alphabetical, calculate alphabetical value
    for (letter = 0, n = strlen(word); letter < n; letter++)
    {   
        word[letter] = tolower(word[letter]);
        if (word[letter] >= 'a' && word[letter] <= 'z') 
        {
            int ascii_value = word[letter];
            int alpha_index = ascii_value - 97;
            int value = POINTS[alpha_index];
            score += value;
        }

    }
    return score;
}