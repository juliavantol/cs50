#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start_size;
    do 
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size;
    do 
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    int years;
    // Calculate number of years until we reach threshold
    for (years = 0; start_size < end_size; years++)
    {
        int birth = start_size / 3;
        int death = start_size / 4;
        start_size = start_size + birth - death;
    }

    // Print number of years
    printf("Years: %i\n", years);
}