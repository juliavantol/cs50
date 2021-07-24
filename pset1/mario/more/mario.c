#include <stdio.h>
#include <cs50.h>

int main(void) 

{

    // prompt user for height of pyramid
    int height;
    do
    {

        height = get_int("Height: ");

    } 
    while (height <= 0 || height > 8);

    // create a row with every iteration 
    int line = 1;
    for (int rows = 0; rows < height; rows++)
    {
        // for each row
        // print spaces
        int spaces = height - line;
        for (int i = 0; i < spaces; i++) 
        {
            printf(" ");
        } 

        // print left hashes
        for (int j = 0; j < line; j++) 
        {   
            printf("#");
        } 

        // print gap
        for (int gap = 0; gap < 2; gap++) 
        {   
            printf(" ");
        } 

        // print right hashes
        for (int r = 0; r < line; r++) 
        {   
            printf("#");
        } 
      
        printf("\n");
        line++;
    }

}