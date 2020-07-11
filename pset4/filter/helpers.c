#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the 3 colors
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;
            // Round to the nearest int
            int avgRound = round(avg);
            // Set the same value to the 3 channels
            image[i][j].rgbtBlue = avgRound;
            image[i][j].rgbtGreen = avgRound;
            image[i][j].rgbtRed = avgRound;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            // Calculate each sepia value with the given formula
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            // Round the values and check that don´t exceed the 255 limit
            int sepiaRedRound = round(sepiaRed);
            if (sepiaRedRound > 255)
            {
                sepiaRedRound = 255;
            }
            int sepiaGreenRound = round(sepiaGreen);
            if (sepiaGreenRound > 255)
            {
                sepiaGreenRound = 255;
            }
            int sepiaBlueRound = round(sepiaBlue);
            if (sepiaBlueRound > 255)
            {
                sepiaBlueRound = 255;
            }

            // Now we can modify the colors
            image[i][j].rgbtRed = sepiaRedRound;
            image[i][j].rgbtGreen = sepiaGreenRound;
            image[i][j].rgbtBlue = sepiaBlueRound;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns (only until the middle)
        for (int j = 0; j < width - 1 - j; j++)
        {
            // Changes the values
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // We can´t change the value of image[][] because it will affect the next calculations, so we make a new array
    RGBTRIPLE blur[height][width];

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            float qCells = 0;
            // Check if the row above exist
            if (i - 1 >= 0)
            {
                totalRed += image[i - 1][j].rgbtRed;
                totalGreen += image[i - 1][j].rgbtGreen;
                totalBlue += image[i - 1][j].rgbtBlue;
                qCells++;
                // Check if the previous column exist
                if (j - 1 >= 0)
                {
                    totalRed += image[i - 1][j - 1].rgbtRed;
                    totalGreen += image[i - 1][j - 1].rgbtGreen;
                    totalBlue += image[i - 1][j - 1].rgbtBlue;
                    qCells++;
                }
                // Check if the next column exist
                if (j + 1 < width)
                {
                    totalRed += image[i - 1][j + 1].rgbtRed;
                    totalGreen += image[i - 1][j + 1].rgbtGreen;
                    totalBlue += image[i - 1][j + 1].rgbtBlue;
                    qCells++;
                }
            }
            // Current row && Column
            totalRed += image[i][j].rgbtRed;
            totalGreen += image[i][j].rgbtGreen;
            totalBlue += image[i][j].rgbtBlue;
            qCells++;
            // Check if the previous column exist
            if (j - 1 >= 0)
            {
                totalRed += image[i][j - 1].rgbtRed;
                totalGreen += image[i][j - 1].rgbtGreen;
                totalBlue += image[i][j - 1].rgbtBlue;
                qCells++;
            }
            // Check if the next column exist
            if (j + 1 < width)
            {
                totalRed += image[i][j + 1].rgbtRed;
                totalGreen += image[i][j + 1].rgbtGreen;
                totalBlue += image[i][j + 1].rgbtBlue;
                qCells++;
            }
            // Check if the row below exist
            if (i + 1 < height)
            {
                totalRed += image[i + 1][j].rgbtRed;
                totalGreen += image[i + 1][j].rgbtGreen;
                totalBlue += image[i + 1][j].rgbtBlue;
                qCells++;
                // Check if the previous column exist
                if (j - 1 >= 0)
                {
                    totalRed += image[i + 1][j - 1].rgbtRed;
                    totalGreen += image[i + 1][j - 1].rgbtGreen;
                    totalBlue += image[i + 1][j - 1].rgbtBlue;
                    qCells++;
                }
                // Check if the next column exist
                if (j + 1 < width)
                {
                    totalRed += image[i + 1][j + 1].rgbtRed;
                    totalGreen += image[i + 1][j + 1].rgbtGreen;
                    totalBlue += image[i + 1][j + 1].rgbtBlue;
                    qCells++;
                }
            }

            // Calculate the averages
            float avgRed = totalRed / qCells;
            float avgGreen = totalGreen / qCells;
            float avgBlue = totalBlue / qCells;

            // Round
            int newRed = round(avgRed);
            int newGreen = round(avgGreen);
            int newBlue = round(avgBlue);

            blur[i][j].rgbtRed = newRed;
            blur[i][j].rgbtGreen = newGreen;
            blur[i][j].rgbtBlue = newBlue;
        }
    }

    // Once we finish with the calculations we can change our original array
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;
        }
    }
}
