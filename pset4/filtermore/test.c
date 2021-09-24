#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main (void)
{

    RGBTRIPLE array[3][3] =
    {
        {{0,10,25}, {0,10,30}, {40,60,80}},

        {{20,30,90}, {30,40,100}, {80,70,90}},

        {{20,20,40}, {30,10,30}, {50,40,10}}
    };
    
    float gxredSum = 0.0;
            float gxgreenSum = 0.0;
            float gxblueSum = 0.0;

            float gyredSum = 0.0;
            float gygreenSum = 0.0;
            float gyblueSum = 0.0;

    // Loop through all the rows
    for (int row = 0; row < 3; row++)
    {
        // For each pixel, make a 3x3 grid around it
        for (int pixel = 0; pixel < 3; pixel++)
        {
            
            float gxredSum = 0.0;
            float gxgreenSum = 0.0;
            float gxblueSum = 0.0;

            float gyredSum = 0.0;
            float gygreenSum = 0.0;
            float gyblueSum = 0.0;

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

                    float gxblue = array[row + squareRow][pixel + squareWidth].rgbtBlue * gx;
                    float gxgreen = array[row + squareRow][pixel + squareWidth].rgbtGreen * gx;
                    float gxred = array[row + squareRow][pixel + squareWidth].rgbtRed * gx;

                    gxredSum += gxred;
                    gxgreenSum += gxgreen;
                    gxblueSum += gxblueSum;
                    
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
            for (int squareWidth = -1; squareWidth < 2; squareWidth++)
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
                    
                    float gyblue = array[row + squareRow][pixel + squareWidth].rgbtBlue * gy;
                    float gygreen = array[row + squareRow][pixel + squareWidth].rgbtGreen * gy;
                    float gyred = array[row + squareRow][pixel + squareWidth].rgbtRed * gy;

                    gyredSum += gyred;
                    gygreenSum += gygreen;
                    gyblueSum += gyblueSum;

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

            printf("{%f, %f, %f} \n", newBlue, newGreen, newRed);

        }

            


    }




}