#include <stdio.h>
#include <cs50.h>

void hash(int count);

int main(void) {

    // Prompt user for height of pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 0 || height > 8);
    
    int count = 1;
    for (int vertical_rows = 0; vertical_rows < height; vertical_rows++)
    {
        hash(count);
        printf("\n");
        count++;
    }


}

void hash(int count)
{
    for (int i = 0; i < count; i++) {
        printf("x");
    }
}