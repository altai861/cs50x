#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <cs50.h>


bool exist(int i , int j , int height, int width);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int  i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE bases[9];
            int base_counter = 0;

            for (int h = 0; h < 9; h++)
            {
                bases[h].rgbtRed = 0;
                bases[h].rgbtBlue = 0;
                bases[h].rgbtGreen = 0;
            }
            if (exist(i - 1, j - 1, height, width))
            {
                bases[0] = image[i- 1][j- 1];
                base_counter++;
            }
            if (exist(i - 1, j, height, width))
            {
                bases[1] = image[i- 1][j];
                base_counter++;
            }
            if (exist(i - 1, j + 1, height, width))
            {
                bases[2] = image[i- 1][j + 1];
                base_counter++;
            }
            if (exist(i, j - 1, height, width))
            {
                bases[3] = image[i][j- 1];
                base_counter++;
            }
            if (exist(i, j , height, width))
            {
                bases[4] = image[i][j];
                base_counter++;
            }
            if (exist(i , j + 1, height, width))
            {
                bases[5] = image[i][j+ 1];
                base_counter++;
            }
            if (exist(i + 1, j - 1, height, width))
            {
                bases[6] = image[i+ 1][j- 1];
                base_counter++;
            }
            if (exist(i + 1, j , height, width))
            {
                bases[7] = image[i + 1][j];
                base_counter++;
            }
            if (exist(i + 1, j + 1, height, width))
            {
                bases[8] = image[i+ 1][j+ 1];
                base_counter++;
            }
            float sumRed = 0;
            for (int h = 0; h < 9; h++)
            {
                sumRed += bases[h].rgbtRed;
            }
            float avgRed = sumRed / base_counter;

            float sumBlue = 0;
            for (int h = 0; h < 9; h++)
            {
                sumBlue += bases[h].rgbtBlue;
            }
            float avgBlue = sumBlue / base_counter;

            float sumGreen = 0;
            for (int h = 0; h < 9; h++)
            {
                sumGreen += bases[h].rgbtGreen;
            }
            float avgGreen = sumGreen / base_counter;

            copy_image[i][j].rgbtRed = round(avgRed);
            copy_image[i][j].rgbtGreen = round(avgGreen);
            copy_image[i][j].rgbtBlue = round(avgBlue);


        }


    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy_image[i][j];
        }
    }
    return;
}


bool exist(int i , int j , int height, int width)
{
    if (i < 0 || j < 0)
    {
        return false;
    }
    if (i >= height || j >= width)
    {
        return false;
    }
    return true;
}










