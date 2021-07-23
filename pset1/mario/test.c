#include <stdio.h>
#include <cs50.h>

void hash(int count);

int main(void) {

    int count = 2;
    hash(count);


}

void hash(int count)
{
    for (int i = 0; i < count; i++) {
         printf("x");
    }
}
