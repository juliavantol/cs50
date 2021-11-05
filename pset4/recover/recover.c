#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
 
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // TO DO: open memory card
    // FILE *f = fopen(filename, "r");

    // TO DO: Look for beginning of a JPEG
    // Every JPEG starts with a distinct header
    // --> 0xff 0xd8 oxff 0xe(e0 --> ef)
    // Read block into buffer (array of bytes)
    // check first byte of buffer by buffer[0] == 0xff
    // (buffer[3] & 0xf0) == 0xe0

    // TO DO: Open a new JPEG file
    // FILE *img = fopen(filename, "w");
    // TO DO: Write 512 bytes until a new JPEG is found
    
    // TO DO: open memory card
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: [filename]\n");
        return 1;
    }

    string input_file = argv[1];
    FILE *card = fopen(input_file, "r");
    if (card == NULL)
    {
        fclose(card);
        fprintf(stderr, "Could not open %s.\n", input_file);
        return 2;
    }


    int count = 0;
    BYTE buffer[512];

    // TO DO: repeat until end of file
    while ((fread(&buffer, sizeof(BYTE), 512, card) > 0))
    {   
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
 
            char name[10];
            sprintf(name, "%03i.jpg", count);

            FILE* img = fopen(name, "w");

            fwrite(&buffer, sizeof(BYTE), 512, img);
            fclose(img);
            count += 1;
        }   
    }


    // TO DO: repeat until end of file
        // read 512 bytes into a buffer
        // if start of new JPEG
            // if first jpeg
                // start writing
            // else
            // close file and open new file
        // else
            // if already found jpeg, keep writing



    fclose(card);
}