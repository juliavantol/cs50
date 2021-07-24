#include <stdio.h>
#include <cs50.h>


int main(void) {

    // Prompt user for height of pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height <= 0 || height > 8);
    
    int line = 1;
    for (int vertical_rows = 0; vertical_rows < height; vertical_rows++)
    {

        int spaces = height - line;
        for (int j = 0; j < spaces; j++) 
        {
            printf(" ");
        }

        for (int i = 0; i < line; i++) 
        {   
            printf("#");
        }   
        printf("\n");
        line++;
    }


}