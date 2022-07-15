#include "helpers.h"

#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixel_grayscale = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            pixel_grayscale = round(pixel_grayscale / 3.0);

            image[i][j].rgbtRed = pixel_grayscale;
            image[i][j].rgbtGreen = pixel_grayscale;
            image[i][j].rgbtBlue = pixel_grayscale;
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
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp_count = 0;
            RGBTRIPLE temp[9];

            bool fill[3][3];
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    fill[k][l] = true;

            for (int k = 0; k < 3; k++)
            {
                if (i == 0)
                    fill[0][k] = false;
                if (i == height - 1)
                    fill[2][k] = false;
                if (j == 0)
                    fill[k][0] = false;
                if (j == width - 1)
                    fill[k][2] = false;
            }

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (fill[k + 1][l + 1])
                    {
                        temp[temp_count] = image[i + k][j + l];
                        temp_count++;
                    }
                }
            }

            int r = temp_count/2;
            int g = temp_count/2;
            int b = temp_count/2;

            for (int k = 0; k < temp_count; k++)
            {
                r += temp[k].rgbtRed;
                g += temp[k].rgbtGreen;
                b += temp[k].rgbtBlue;
            }

            buffer[i][j].rgbtRed = round(r / temp_count);
            buffer[i][j].rgbtGreen = round(g / temp_count);
            buffer[i][j].rgbtBlue = round(b / temp_count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel[3][3];

            bool fill[3][3];
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    fill[k][l] = false;

            for (int k = 0; k < 3; k++)
            {
                if (i == 0)
                    fill[0][k] = true;
                if (i == height - 1)
                    fill[2][k] = true;
                if (j == 0)
                    fill[k][0] = true;
                if (j == width - 1)
                    fill[k][2] = true;
            }

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (fill[k][l])
                    {
                        pixel[k][l].rgbtRed = 0x00;
                        pixel[k][l].rgbtGreen = 0x00;
                        pixel[k][l].rgbtBlue = 0x00;
                    }
                    else
                    {
                        pixel[k][l] = image[i + k - 1][j + l - 1];
                    }
                }
            }

            // Gx
            int redX = 0;
            int greenX = 0;
            int blueX = 0;

            for (int k = 0; k < 2; k++)
            {
                redX += -1 * pixel[k][0].rgbtRed;
                greenX += -1 * pixel[k][0].rgbtGreen;
                blueX += -1 * pixel[k][0].rgbtBlue;

                redX += -1 * pixel[k + 1][0].rgbtRed;
                greenX += -1 * pixel[k + 1][0].rgbtGreen;
                blueX += -1 * pixel[k + 1][0].rgbtBlue;
            }

            for (int k = 0; k < 2; k++)
            {
                redX += 1 * pixel[k][2].rgbtRed;
                greenX += 1 * pixel[k][2].rgbtGreen;
                blueX += 1 * pixel[k][2].rgbtBlue;

                redX += 1 * pixel[k + 1][2].rgbtRed;
                greenX += 1 * pixel[k + 1][2].rgbtGreen;
                blueX += 1 * pixel[k + 1][2].rgbtBlue;
            }

            // Gy
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            for (int k = 0; k < 2; k++)
            {
                redY += -1 * pixel[0][k].rgbtRed;
                greenY += -1 * pixel[0][k].rgbtGreen;
                blueY += -1 * pixel[0][k].rgbtBlue;

                redY += -1 * pixel[0][k + 1].rgbtRed;
                greenY += -1 * pixel[0][k + 1].rgbtGreen;
                blueY += -1 * pixel[0][k + 1].rgbtBlue;
            }

            for (int k = 0; k < 2; k++)
            {
                redY += 1 * pixel[2][k].rgbtRed;
                greenY += 1 * pixel[2][k].rgbtGreen;
                blueY += 1 * pixel[2][k].rgbtBlue;

                redY += 1 * pixel[2][k + 1].rgbtRed;
                greenY += 1 * pixel[2][k + 1].rgbtGreen;
                blueY += 1 * pixel[2][k + 1].rgbtBlue;
            }
            buffer[i][j].rgbtRed = round(sqrt((redX * redX) + (redY * redY)) > 255 ? 255 : sqrt((redX * redX) + (redY * redY)));
            buffer[i][j].rgbtGreen = round(sqrt((greenX * greenX) + (greenY * greenY)) > 255 ? 255 : sqrt((greenX * greenX) + (greenY * greenY)));
            buffer[i][j].rgbtBlue = round(sqrt((blueX * blueX) + (blueY * blueY)) > 255 ? 255 : sqrt((blueX * blueX) + (blueY * blueY)));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }

    return;
}