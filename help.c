#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

struct musician {
    string name;
    string instrument;
    int year_born;
};

struct car {
    int year;
    string plate;
    int odometer;
};

void print_musician(struct musician m);

int main()
{
    // Step 1: Greate a 'john' variable
    struct musician john;
    
    // Step 2: Set the fields to the appropriate values
    john.name = "John";
    john.instrument = "guitar, vocals";
    john.year_born = 1940;

    // Print values
    print_musician(john);

    struct car *mycar = malloc(sizeof(struct car));

    (*mycar).year = 2011;
    strcpy((*mycar). plate, "CS50");
    (*mycar).odometer = 50505;

    free();

  
}

// Step 3: create a print function
void print_musician(struct musician m)
{
    printf("Name: %s\n", m.name);
    printf("Instrument: %s\n", m.instrument);
    printf("Born: %i\n", m.year_born);
}