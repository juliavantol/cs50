#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all through the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel in the row, do this
        for (int pixel = 0; pixel < width; pixel++)
        {
            float blue = image[row][pixel].rgbtBlue;
            float green = image[row][pixel].rgbtGreen;
            float red = image[row][pixel].rgbtRed;

            float average = roundf((blue + green + red) / 3);

            image[row][pixel].rgbtBlue = average;
            image[row][pixel].rgbtGreen = average;
            image[row][pixel].rgbtRed = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all through the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel in the row, do this
        for (int pixel = 0; pixel < width; pixel++)
        {
            float blue = image[row][pixel].rgbtBlue;
            float green = image[row][pixel].rgbtGreen;
            float red = image[row][pixel].rgbtRed;

            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            float sepiaBlue = .272 * red + .534 * green + .131 * blue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[row][pixel].rgbtBlue = roundf(sepiaBlue);
            image[row][pixel].rgbtGreen = roundf(sepiaGreen);
            image[row][pixel].rgbtRed = roundf(sepiaRed);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    // Loop all through the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel in the row, do this
        for (int pixel = 0; pixel < half; pixel++)
        {
            RGBTRIPLE pixelLeft = image[row][pixel];
            int test = width - 1;
            RGBTRIPLE pixelRight = image[row][test - pixel];

            image[row][pixel] = pixelRight;
            image[row][test - pixel] = pixelLeft;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop all through the rows
    for (int row = 1; row < (height - 1); row++)
    {

        // For each pixel in the row, do this
        for (int pixel = 1; pixel < (width - 1); pixel++)
        {

            int average = 0;
            int sum = 0;



        }
    }

    return;
}
