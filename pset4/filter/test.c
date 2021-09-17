#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void) 
{ 

int width = get_int("Width: ");
int half = width / 2;

for(int increment = 0; increment < half; increment++)
{
    printf("%i\n", increment);
}


}