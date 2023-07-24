#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;

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
            RGBTRIPLE buffer = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE clone[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            clone[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed;
            int avgGreen;
            int avgBlue;


            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;

            int counter = 0;
            if(i != 0)
            {
                totalRed = totalRed + image[i - 1][j].rgbtRed;
                totalGreen = totalGreen + image[i - 1][j].rgbtGreen;
                totalBlue = totalBlue + image[i - 1][j].rgbtBlue;
                counter++;
            }
            if(j != 0 && i != 0)
            {
                totalRed = totalRed + image[i - 1][j - 1].rgbtRed;
                totalGreen = totalGreen + image[i - 1][j - 1].rgbtGreen;
                totalBlue = totalBlue + image[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if (j != 0)
            {
                totalRed = totalRed + image[i][j - 1].rgbtRed;
                totalGreen = totalGreen + image[i][j - 1].rgbtGreen;
                totalBlue = totalBlue + image[i][j - 1].rgbtBlue;
                counter++;
            }
            if (i != height - 1 && j != 0)
            {
                totalRed = totalRed + image[i + 1][j - 1].rgbtRed;
                totalGreen = totalGreen + image[i + 1][j - 1].rgbtGreen;
                totalBlue = totalBlue + image[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if (i != height - 1)
            {
                totalRed = totalRed + image[i + 1][j].rgbtRed;
                totalGreen = totalGreen + image[i + 1][j].rgbtGreen;
                totalBlue = totalBlue + image[i + 1][j].rgbtBlue;
                counter++;
            }
            if (i != height - 1 && j != width - 1)
            {
                totalRed = totalRed + image[i + 1][j + 1].rgbtRed;
                totalGreen = totalGreen + image[i + 1][j + 1].rgbtGreen;
                totalBlue = totalBlue + image[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            if (j != width - 1)
            {
                totalRed = totalRed + image[i][j + 1].rgbtRed;
                totalGreen = totalGreen + image[i][j + 1].rgbtGreen;
                totalBlue = totalBlue + image[i][j + 1].rgbtBlue;
                counter++;
            }
            if (i != 0 && j != width - 1)
            {
                totalRed = totalRed + image[i - 1][j + 1].rgbtRed;
                totalGreen = totalGreen + image[i - 1][j + 1].rgbtGreen;
                totalBlue = totalBlue + image[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            totalRed = totalRed + image[i][j].rgbtRed;
            totalGreen = totalGreen + image[i][j].rgbtGreen;
            totalBlue = totalBlue + image[i][j].rgbtBlue;
            counter++;
            avgRed = round(totalRed / (float)counter);
            avgGreen = round(totalGreen / (float)counter);
            avgBlue = round(totalBlue / (float)counter);
            clone[i][j].rgbtRed = avgRed;
            clone[i][j].rgbtGreen = avgGreen;
            clone[i][j].rgbtBlue = avgBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = clone[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE clone[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1))
            {
                if (i == 0 && j == 0)
                {
                    int gxRed = image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                    int gxGreen = image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                    int gxBlue = image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;


                    int gyRed = image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                    int gyGreen = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                    int gyBlue = image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;


                    int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                    int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                    int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                    clone[i][j].rgbtRed = avgRed;
                    clone[i][j].rgbtGreen = avgGreen;
                    clone[i][j].rgbtBlue = avgBlue;
                }
                else if (i == 0 && j == width - 1)
                {
                    int gxRed = image[i][j - 1].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * (-1);
                    int gxGreen = image[i][j - 1].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * (-1);
                    int gxBlue = image[i][j - 1].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue * (-1);


                    int gyRed = image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2;
                    int gyGreen = image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2;
                    int gyBlue = image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2;


                    int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                    int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                    int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                    clone[i][j].rgbtRed = avgRed;
                    clone[i][j].rgbtGreen = avgGreen;
                    clone[i][j].rgbtBlue = avgBlue;
                }
                else if (i == height - 1 && j == 0 )
                {
                    int gxRed = image[i - 1 ][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2;
                    int gxGreen = image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2;
                    int gxBlue = image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2;


                    int gyRed = image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1);
                    int gyGreen = image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1);
                    int gyBlue = image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1);


                    int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                    int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                    int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                    clone[i][j].rgbtRed = avgRed;
                    clone[i][j].rgbtGreen = avgGreen;
                    clone[i][j].rgbtBlue = avgBlue;
                }
                else if (i == height - 1 && j == width - 1)
                {
                    int gxRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed * (-2);
                    int gxGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i][j - 1].rgbtGreen * (-2);
                    int gxBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i][j - 1].rgbtBlue * (-2);


                    int gyRed = image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1);
                    int gyGreen = image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1);
                    int gyBlue = image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1);


                    int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                    int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                    int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                    clone[i][j].rgbtRed = avgRed;
                    clone[i][j].rgbtGreen = avgGreen;
                    clone[i][j].rgbtBlue = avgBlue;
                }
            }
            else if (i == 0 && (j != 0 || j != width - 1))
            {
                int gxRed = image[i][j - 1].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * (-1) + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gxGreen = image[i][j - 1].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * (-1) + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gxBlue = image[i][j - 1].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue * (-1) + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;


                int gyRed = image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gyGreen = image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gyBlue = image[i + 1][j - 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;


                int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                clone[i][j].rgbtRed = avgRed;
                clone[i][j].rgbtGreen = avgGreen;
                clone[i][j].rgbtBlue = avgBlue;
            }
            else if ((i != 0 || i != height - 1) && j == width - 1)
            {
                int gxRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * (-1);
                int gxGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i][j - 1].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * (-1);
                int gxBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i][j - 1].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue * (-1);


                int gyRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2;
                int gyGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2;
                int gyBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2;



                int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                clone[i][j].rgbtRed = avgRed;
                clone[i][j].rgbtGreen = avgGreen;
                clone[i][j].rgbtBlue = avgBlue;
            }
            else if (i == height - 1 && (j != 0 || j != width - 1))
            {
                int gxRed = image[i][j - 1].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1) + image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed * 1;
                int gxGreen = image[i][j - 1].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen * 1;
                int gxBlue = image[i][j - 1].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue * 1;


                int gyRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1);
                int gyGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1);
                int gyBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1);



                int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                clone[i][j].rgbtRed = avgRed;
                clone[i][j].rgbtGreen = avgGreen;
                clone[i][j].rgbtBlue = avgBlue;
            }
            else if ((i != 0 || i != height - 1) && j == 0)
            {
                int gxRed = image[i - 1][j + 1].rgbtRed * -1 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gxGreen = image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gxBlue = image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;


                int gyRed = image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1) + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gyGreen = image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gyBlue = image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;


                int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                clone[i][j].rgbtRed = avgRed;
                clone[i][j].rgbtGreen = avgGreen;
                clone[i][j].rgbtBlue = avgBlue;
            }
            else
            {

                int gxRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i][j - 1].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * (-1) + image[i - 1][j + 1].rgbtRed * 1 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gxGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i][j - 1].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * (-1) + image[i - 1][j + 1].rgbtGreen * 1 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gxBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i][j - 1].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue * (-1) + image[i - 1][j + 1].rgbtBlue * 1 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1;

                int gyRed = image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1) + image[i + 1][j - 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1;
                int gyGreen = image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1) + image[i + 1][j - 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1;
                int gyBlue = image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1) + image[i + 1][j - 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue ;

                int avgRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                int avgGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                int avgBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));


                clone[i][j].rgbtRed = avgRed;
                clone[i][j].rgbtGreen = avgGreen;
                clone[i][j].rgbtBlue = avgBlue;
            }
        }
    }
    image = clone;
    return;
}
