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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // We can´t change the value of image[][] because it will affect the next calculations, so we make a new array
    RGBTRIPLE edge[height][width];

    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            int totalRedGx = 0;
            int totalRedGy = 0;
            int totalGreenGx = 0;
            int totalGreenGy = 0;
            int totalBlueGx = 0;
            int totalBlueGy = 0;

            // Check if the row above exist
            if (i - 1 >= 0)
            {
                totalRedGx += image[i - 1][j].rgbtRed * 0;
                totalRedGy += image[i - 1][j].rgbtRed * -2;

                totalGreenGx += image[i - 1][j].rgbtGreen * 0;
                totalGreenGy += image[i - 1][j].rgbtGreen * -2;

                totalBlueGx += image[i - 1][j].rgbtBlue * 0;
                totalBlueGy += image[i - 1][j].rgbtBlue * -2;

                // Check if the previous column exist
                if (j - 1 >= 0)
                {
                    totalRedGx += image[i - 1][j - 1].rgbtRed * -1;
                    totalRedGy += image[i - 1][j - 1].rgbtRed * -1;

                    totalGreenGx += image[i - 1][j - 1].rgbtGreen * -1;
                    totalGreenGy += image[i - 1][j - 1].rgbtGreen * -1;

                    totalBlueGx += image[i - 1][j - 1].rgbtBlue * -1;
                    totalBlueGy += image[i - 1][j - 1].rgbtBlue * -1;
                }

                // Check if the next column exist
                if (j + 1 < width)
                {
                    totalRedGx += image[i - 1][j + 1].rgbtRed * 1;
                    totalRedGy += image[i - 1][j + 1].rgbtRed * -1;

                    totalGreenGx += image[i - 1][j + 1].rgbtGreen * 1;
                    totalGreenGy += image[i - 1][j + 1].rgbtGreen * -1;

                    totalBlueGx += image[i - 1][j + 1].rgbtBlue * 1;
                    totalBlueGy += image[i - 1][j + 1].rgbtBlue * -1;
                }
            }

            // Current row && Column
            totalRedGx += image[i][j].rgbtRed * 0;
            totalRedGy += image[i][j].rgbtRed * 0;

            totalGreenGx += image[i][j].rgbtGreen * 0;
            totalGreenGy += image[i][j].rgbtGreen * 0;

            totalBlueGx += image[i][j].rgbtBlue * 0;
            totalBlueGy += image[i][j].rgbtBlue * 0;

            // Check if the previous column exist
            if (j - 1 >= 0)
            {
                totalRedGx += image[i][j - 1].rgbtRed * -2;
                totalRedGy += image[i][j - 1].rgbtRed * 0;

                totalGreenGx += image[i][j - 1].rgbtGreen * -2;
                totalGreenGy += image[i][j - 1].rgbtGreen * 0;

                totalBlueGx += image[i][j - 1].rgbtBlue * -2;
                totalBlueGy += image[i][j - 1].rgbtBlue * 0;
            }

            // Check if the next column exist
            if (j + 1 < width)
            {
                totalRedGx += image[i][j + 1].rgbtRed * 2;
                totalRedGy += image[i][j + 1].rgbtRed * 0;

                totalGreenGx += image[i][j + 1].rgbtGreen * 2;
                totalGreenGy += image[i][j + 1].rgbtGreen * 0;

                totalBlueGx += image[i][j + 1].rgbtBlue * 2;
                totalBlueGy += image[i][j + 1].rgbtBlue * 0;
            }

            // Check if the row below exist
            if (i + 1 < height)
            {
                totalRedGx += image[i + 1][j].rgbtRed * 0;
                totalRedGy += image[i + 1][j].rgbtRed * 2;

                totalGreenGx += image[i + 1][j].rgbtGreen * 0;
                totalGreenGy += image[i + 1][j].rgbtGreen * 2;

                totalBlueGx += image[i + 1][j].rgbtBlue * 0;
                totalBlueGy += image[i + 1][j].rgbtBlue * 2;

                // Check if the previous column exist
                if (j - 1 >= 0)
                {
                    totalRedGx += image[i + 1][j - 1].rgbtRed * -1;
                    totalRedGy += image[i + 1][j - 1].rgbtRed * 1;

                    totalGreenGx += image[i + 1][j - 1].rgbtGreen * -1;
                    totalGreenGy += image[i + 1][j - 1].rgbtGreen * 1;

                    totalBlueGx += image[i + 1][j - 1].rgbtBlue * -1;
                    totalBlueGy += image[i + 1][j - 1].rgbtBlue * 1;
                }

                // Check if the next column exist
                if (j + 1 < width)
                {
                    totalRedGx += image[i + 1][j + 1].rgbtRed * 1;
                    totalRedGy += image[i + 1][j + 1].rgbtRed * 1;

                    totalGreenGx += image[i + 1][j + 1].rgbtGreen * 1;
                    totalGreenGy += image[i + 1][j + 1].rgbtGreen * 1;

                    totalBlueGx += image[i + 1][j + 1].rgbtBlue * 1;
                    totalBlueGy += image[i + 1][j + 1].rgbtBlue * 1;
                }
            }

            // Calculate the averages
            double red = sqrt(powf(totalRedGx, 2) + powf(totalRedGy, 2));
            double green = sqrt(powf(totalGreenGx, 2) + powf(totalGreenGy, 2));
            double blue = sqrt(powf(totalBlueGx, 2) + powf(totalBlueGy, 2));

            // Round and 255 cap
            int newRed = red > 255 ? 255 : round(red);
            int newGreen = green > 255 ? 255 : round(green);
            int newBlue = blue > 255 ? 255 : round(blue);

            edge[i][j].rgbtRed = newRed;
            edge[i][j].rgbtGreen = newGreen;
            edge[i][j].rgbtBlue = newBlue;
        }
    }

    // Once we finish with the calculations we can change our original array
    // Iterate over rows
    for (int i = 0; i < height; i++)
    {
        // Iterate over columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = edge[i][j].rgbtRed;
            image[i][j].rgbtGreen = edge[i][j].rgbtGreen;
            image[i][j].rgbtBlue = edge[i][j].rgbtBlue;
        }
    }
}
