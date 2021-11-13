#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void count_all(string text, float *letter_count, float *word_count, float *sentence_count);

int main(void) 
{

    // Get text input from user
    string text = get_string("Text: ");

    float letter_count = 0.00;
    float word_count = 1.00;
    float sentence_count = 0.00;

    // Run function to count all of the necessary data and store in pointers
    count_all(text, &letter_count, &word_count, &sentence_count);

    // Calculate average per 100 words
    float av_letters = (letter_count / word_count) * 100;
    float av_sentences = (sentence_count / word_count) * 100; 

    // Calculate grade level, round it to nearest integer and store in int
    int grade_level = round(0.0588 * av_letters - 0.296 * av_sentences - 15.8);

    // Determine which message to print by looking at grade level
    if (grade_level >= 16) 
    {
        printf("Grade 16+\n");
    }
    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
    
}

// Function to count all the necessary data
void count_all(string text, float *letter_count, float *word_count, float *sentence_count) 
{
    int i, n;    
    for (i = 0, n = strlen(text); i < n; i++)
    {   
        // If character is alphabetical, increase letter count
        if (isalpha(text[i]))
        {
            *letter_count += 1;
        }

        // If character is an empty space, increase word count
        if (text[i] == 32)
        {
            *word_count += 1;
        }

        // If character is period, question or exclamation mark, increase sentence count
        if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {
            *sentence_count += 1;
        }
    }

}