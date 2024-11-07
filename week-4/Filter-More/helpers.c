#include <stdio.h>
#include <math.h>

#include "helpers.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

static int checkLimit(int num)
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
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int grayVal = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = grayVal;
            image[i][j].rgbtGreen = grayVal;
            image[i][j].rgbtBlue = grayVal;
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
            int counter = 0;
            for (int k = max(0, i - 1); k <= min(height - 1, i + 1); k++)
            {
                for (int l = max(0, j - 1); l <= min(width - 1, j + 1); l++)
                {
                    redSum += copy[k][l].rgbtRed;
                    greenSum += copy[k][l].rgbtGreen;
                    blueSum += copy[k][l].rgbtBlue;
                    counter++;
                }
            }

            redSum = round(redSum / (float) counter);
            greenSum = round(greenSum / (float) counter);
            blueSum = round(blueSum / (float) counter);

            image[i][j].rgbtRed = redSum;
            image[i][j].rgbtGreen = greenSum;
            image[i][j].rgbtBlue = blueSum;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3]= {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            int redGx = 0, greenGx = 0, blueGx = 0;
            int redGy = 0, greenGy = 0, blueGy = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    int kernelRow = k - (i - 1);
                    int kernelCol = l - (j - 1);
                    if (k < 0 || l < 0 || k >= height || l >= width)
                    {
                        continue;
                    }
                    else
                    {
                        redGx += copy[k][l].rgbtRed * gx[kernelRow][kernelCol];
                        greenGx += copy[k][l].rgbtGreen * gx[kernelRow][kernelCol];
                        blueGx += copy[k][l].rgbtBlue * gx[kernelRow][kernelCol];

                        redGy += copy[k][l].rgbtRed * gy[kernelRow][kernelCol];
                        greenGy += copy[k][l].rgbtGreen * gy[kernelRow][kernelCol];
                        blueGy += copy[k][l].rgbtBlue * gy[kernelRow][kernelCol];
                    }
                }
            }

            int redNewVal = checkLimit(round(sqrt((redGx * redGx) + (redGy * redGy))));
            int greenNewVal = checkLimit(round(sqrt((greenGx * greenGx) + (greenGy * greenGy))));
            int blueNewVal = checkLimit(round(sqrt((blueGx * blueGx) + (blueGy * blueGy))));

            image[i][j].rgbtRed = redNewVal;
            image[i][j].rgbtGreen = greenNewVal;
            image[i][j].rgbtBlue = blueNewVal;
        }
    }
    return;
}
