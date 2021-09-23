#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <cs50.h>

bool checkPixel(int pixel_row, int pixel_width, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all through the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel in the row, calculate average of its colors
        for (int pixel = 0; pixel < width; pixel++)
        {
            float blue = image[row][pixel].rgbtBlue;
            float green = image[row][pixel].rgbtGreen;
            float red = image[row][pixel].rgbtRed;
            float average = roundf((blue + green + red) / 3);

            // Set new color values
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
        // For each pixel in the row, calculate sepia values
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

            // Set new color values
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

    // Loop through all the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel in the row, swap pixels at the furthest ends
        for (int pixel = 0; pixel < half; pixel++)
        {
            RGBTRIPLE pixelLeft = image[row][pixel];
            int lastPlace = width - 1;
            RGBTRIPLE pixelRight = image[row][lastPlace - pixel];
            image[row][pixel] = pixelRight;
            image[row][lastPlace - pixel] = pixelLeft;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image in an array
    RGBTRIPLE copyImage[height][width];

    // Loop through all the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel, make a 3x3 grid around it
        for (int pixel = 0; pixel < width; pixel++)
        {

            float redSum = 0.0;
            float greenSum = 0.0;
            float blueSum = 0.0;
            int counter = 0;

            // Loop around the pixel to make a square
            for (int squareRow = 1; squareRow > -2; squareRow--)
            {
                for (int squareWidth = 1; squareWidth > -2; squareWidth--)
                {
                    // Only add the pixel to the sums if the pixel is not out of bounds
                    if (checkPixel((row + squareRow), (pixel + squareWidth), height, width) == true)
                    {
                        redSum += image[row + squareRow][pixel + squareWidth].rgbtRed;
                        greenSum += image[row + squareRow][pixel + squareWidth].rgbtGreen;
                        blueSum += image[row + squareRow][pixel + squareWidth].rgbtBlue;
                        counter += 1;
                    }
                }
            }

            // Store newly calculated values in temporary array
            copyImage[row][pixel].rgbtRed = roundf(redSum / counter);
            copyImage[row][pixel].rgbtGreen = roundf(greenSum / counter);
            copyImage[row][pixel].rgbtBlue = roundf(blueSum / counter);

        }
    }

    // Copy new values from the copied array to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copyImage[i][j];
        }
    }
}

// Function to check whether a pixel is out of bounds
bool checkPixel(int pixel_row, int pixel_width, int height, int width)
{
    // Return false if pixel is out of bounds
    if (pixel_row < 0 || pixel_row > (height - 1) || pixel_width < 0 || pixel_width > (width - 1))
    {
        return false;
    }
    return true;
}