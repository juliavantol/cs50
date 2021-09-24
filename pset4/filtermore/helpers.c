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


    float gxredSum = 0.0;
    float gxgreenSum = 0.0;
    float gxblueSum = 0.0;

    float gyredSum = 0.0;
    float gygreenSum = 0.0;
    float gyblueSum = 0.0;

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

            int gx = 1;

            // printf("current pixel: {%d, %d, %d} \n", array[row][pixel].rgbtBlue, array[row][pixel].rgbtGreen, array[row][pixel].rgbtRed);
            // Loop around the pixel to make a square
            for (int squareRow = 1; squareRow > -2; squareRow--)
            {

                if (squareRow == 0)
                {
                    gx = 2;
                }
                else
                {
                    gx = 1;
                }

                for (int squareWidth = 1; squareWidth > -2; squareWidth--)
                {

                    float gxblue = image[row + squareRow][pixel + squareWidth].rgbtBlue * gx;
                    float gxgreen = image[row + squareRow][pixel + squareWidth].rgbtGreen * gx;
                    float gxred = image[row + squareRow][pixel + squareWidth].rgbtRed * gx;

                    gxredSum += gxred;
                    gxgreenSum += gxgreen;
                    gxblueSum += gxblue;
                    
                    // printf("gx: {%d, %d, %d} * %i   ", array[row + squareRow][pixel + squareWidth].rgbtBlue, array[row + squareRow][pixel + squareWidth].rgbtGreen, array[row + squareRow][pixel + squareWidth].rgbtRed, gx);
                    if (squareRow == 0)
                    {
                        gx = gx - 2;
                    }
                    else
                    {
                        gx = gx - 1;
                    }

                }
               
            }


            int gy = -1;
            int squareWidth = -1;
            // Loop around the pixel to make a square
            for (squareWidth = -1; squareWidth < 2; squareWidth++)
            {
                
                if (squareWidth == 0)
                {
                    gy = -2;
                }
                else
                {
                    gy = -1;
                }

                for (int squareRow = -1; squareRow < 2; squareRow++)
                {
                    
                    float gyblue = image[row + squareRow][pixel + squareWidth].rgbtBlue * gy;
                    float gygreen = image[row + squareRow][pixel + squareWidth].rgbtGreen * gy;
                    float gyred = image[row + squareRow][pixel + squareWidth].rgbtRed * gy;

                    gyredSum += gyred;
                    gygreenSum += gygreen;
                    gyblueSum += gyblue;

                   // printf("gy: {%d, %d, %d} * %i  ", array[row + squareRow][pixel + squareWidth].rgbtBlue, array[row + squareRow][pixel + squareWidth].rgbtGreen, array[row + squareRow][pixel + squareWidth].rgbtRed, gy);
                    
                    if (squareWidth == 0)
                    {
                        gy = gy + 2;
                    }
                    else
                    {
                        gy = gy + 1;
                    }

                }
   


            }

            float newRed = roundf(sqrt((gxredSum * gxredSum) + (gyredSum * gyredSum)));
            float newGreen = roundf(sqrt((gxgreenSum * gxgreenSum) + (gygreenSum * gygreenSum)));
            float newBlue = roundf(sqrt((gxblueSum * gxblueSum) + (gyblueSum * gyblueSum)));

          
            if (newRed > 255)
            {
                newRed = 255;
            }
        
            if (newGreen > 255)
            {
                newGreen = 255;
            }
        
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            // Store newly calculated values in temporary array
            copyImage[row][pixel].rgbtRed = newRed;
            copyImage[row][pixel].rgbtGreen = newGreen;
            copyImage[row][pixel].rgbtBlue = newBlue;

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
