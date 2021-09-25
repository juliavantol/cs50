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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image in an array
    RGBTRIPLE copyImage[height][width];

    // Store the gx and gy values in 2D arrays for easy referencing
    int gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
 
    float gxred, gxblue, gxgreen, gyred, gygreen, gyblue, gxredSum, gxgreenSum, gxblueSum, gyredSum, gygreenSum, gyblueSum;
    int i, j, squareRow, squareWidth;

    // Loop through all the rows
    for (int row = 0; row < height; row++)
    {
        // For each pixel, make a 3x3 grid around it
        for (int pixel = 0; pixel < width; pixel++)
        {
            
            gxredSum = 0.0;
            gxgreenSum = 0.0;
            gxblueSum = 0.0;

            gyredSum = 0.0;
            gygreenSum = 0.0;
            gyblueSum = 0.0;

            // Loop around the pixel to make a square
            for (squareRow = 1, i = 0; squareRow > -2; squareRow--, i++)
            {
                for (squareWidth = 1, j = 0; squareWidth > -2; squareWidth--, j++)
                {
                    // If the pixel is out of bounds, set it to 0.0
                    if (checkPixel((row + squareRow), (pixel + squareWidth), height, width) == true)
                    {
                        gxblue = image[row + squareRow][pixel + squareWidth].rgbtBlue * gx[i][j];
                        gxgreen = image[row + squareRow][pixel + squareWidth].rgbtGreen * gx[i][j];
                        gxred = image[row + squareRow][pixel + squareWidth].rgbtRed * gx[i][j];

                        gyblue = image[row + squareRow][pixel + squareWidth].rgbtBlue * gy[i][j];
                        gygreen = image[row + squareRow][pixel + squareWidth].rgbtGreen * gy[i][j];
                        gyred = image[row + squareRow][pixel + squareWidth].rgbtRed * gy[i][j];
                    } 
                    else 
                    {
                        gxred = 0.0;
                        gxgreen = 0.0;
                        gxblue = 0.0;
                        gyblue = 0.0;
                        gygreen = 0.0;
                        gyred = 0.0;
                    }

                    // Add the calculated values to their sum
                    gxredSum += gxred;
                    gxgreenSum += gxgreen;
                    gxblueSum += gxblue;

                    gyredSum += gyred;
                    gygreenSum += gygreen;
                    gyblueSum += gyblue;
                        
                }
            }

            // Calculate final color values
            float newRed = roundf(sqrt((gxredSum * gxredSum) + (gyredSum * gyredSum)));
            float newGreen = roundf(sqrt((gxgreenSum * gxgreenSum) + (gygreenSum * gygreenSum)));
            float newBlue = roundf(sqrt((gxblueSum * gxblueSum) + (gyblueSum * gyblueSum)));

            // Cap the values at 255
            newRed = newRed > 255 ? 255 : newRed;
            newGreen = newGreen > 255 ? 255 : newGreen;
            newBlue = newBlue > 255 ? 255 : newBlue;
          
            // Store final values in temporary array
            copyImage[row][pixel].rgbtRed = newRed;
            copyImage[row][pixel].rgbtGreen = newGreen;
            copyImage[row][pixel].rgbtBlue = newBlue;

        }

    }

    // Copy new values from the copied array to the image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = copyImage[i][j];
        }
    }
}
