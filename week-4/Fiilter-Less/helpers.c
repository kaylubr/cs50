#include <math.h>

#include "helpers.h"

static int checkCap(int num)
{
    if (num > 255)
    {
        return 255;
    }

    return num;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // Compute the grayscale value of the byte
            int newVal = round((blue + green + red) / 3.0);

            // Update to grayscale based on the computed values
            image[i][j].rgbtBlue = newVal;
            image[i][j].rgbtGreen = newVal;
            image[i][j].rgbtRed = newVal;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Extract the rbg values of the byte
            int origRed = image[i][j].rgbtRed;
            int origGreen = image[i][j].rgbtGreen;
            int origBlue = image[i][j].rgbtBlue;

            // Compute sepia RGB values
            int sepiaRed = round(0.393 * origRed + 0.769 * origGreen + 0.189 * origBlue);
            int sepiaGreen = round(0.349 * origRed + 0.686 * origGreen + 0.168 * origBlue);
            int sepiaBlue = round(0.272 * origRed + 0.534 * origGreen + 0.1311 * origBlue);

            // Replace the values with the computed sepia values
            image[i][j].rgbtRed = checkCap(sepiaRed);
            image[i][j].rgbtGreen = checkCap(sepiaGreen);
            image[i][j].rgbtBlue = checkCap(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 || l < 0 || k == height || l == width)
                    {
                        continue;
                    }
                    else
                    {
                        redSum += copy[k][l].rgbtRed;
                        greenSum += copy[k][l].rgbtGreen;
                        blueSum += copy[k][l].rgbtBlue;
                        count++;
                    }
                }
            }

            redSum = round(redSum / (float) count);
            greenSum = round(greenSum / (float) count);
            blueSum = round(blueSum / (float) count);

            image[i][j].rgbtRed = redSum;
            image[i][j].rgbtGreen = greenSum;
            image[i][j].rgbtBlue = blueSum;
        }
    }
}
