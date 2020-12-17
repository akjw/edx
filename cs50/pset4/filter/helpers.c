#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r ++)
    {
        for (int c = 0; c < width; c++)
        {
            int average = round((float)(image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3);
            image[r][c].rgbtBlue = average;
            image[r][c].rgbtGreen = average;
            image[r][c].rgbtRed = average;
        }
    }
    return;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r ++)
    {
        for (int c = 0; c < width; c++)
        {
            int colors[3];
            colors[0] = round(.393 * image[r][c].rgbtRed + .769 * image[r][c].rgbtGreen + .189 * image[r][c].rgbtBlue);
            colors[1] = round(.349 * image[r][c].rgbtRed + .686 * image[r][c].rgbtGreen + .168 * image[r][c].rgbtBlue);
            colors[2] = round(.272 * image[r][c].rgbtRed + .534 * image[r][c].rgbtGreen + .131 * image[r][c].rgbtBlue);

            for (int i = 0; i < 3; i++)
            {
                if (colors[i] > 255)
                {
                    colors[i] = 255;
                }
            }

            image[r][c].rgbtBlue = colors[2];
            image[r][c].rgbtGreen = colors[1];
            image[r][c].rgbtRed = colors[0];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle;

    if (width % 2 == 0)
    {
        middle = width / 2;
    }
    else
    {
        middle = floor(width / 2);
    }

    for (int r = 0; r < height; r ++)
    {
        for (int c = 0; c < middle; c++)
        {
            int o = width - 1 - c;
            RGBTRIPLE temp;
            temp = image[r][c];
            image[r][c].rgbtRed = image[r][o].rgbtRed;
            image[r][c].rgbtGreen = image[r][o].rgbtGreen;
            image[r][c].rgbtBlue = image[r][o].rgbtBlue;
            image[r][o].rgbtRed = temp.rgbtRed;
            image[r][o].rgbtGreen = temp.rgbtGreen;
            image[r][o].rgbtBlue = temp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred_img[height][width];
    for (int r = 0; r < height; r ++)
    {
        for (int c = 0; c < width; c++)
        {
            int cells = 1;
            int top = 0;
            int bottom = 0;
            int left = 0;
            int right = 0;
            int totalRed = image[r][c].rgbtRed;
            int totalGreen = image[r][c].rgbtGreen;
            int totalBlue = image[r][c].rgbtBlue;
            // if top row exists
            if (r - 1 > -1)
            {
                top = 1;
            }
            // if bottom row exists
            if (r + 1 < height)
            {
                bottom = 1;
            }
            // if left col exists
            if (c - 1 > -1)
            {
                left = 1;
            }
            // if right col exists
            if (c + 1 < width)
            {
                right = 1;
            }

            // top row left col
            if (top && left)
            {
                cells++;
                totalRed += image[r - 1][c - 1].rgbtRed;
                totalGreen += image[r - 1][c - 1].rgbtGreen;
                totalBlue += image[r - 1][c - 1].rgbtBlue;
            }
            // top row middle col
            if (top)
            {
                cells++;
                totalRed += image[r - 1][c].rgbtRed;
                totalGreen += image[r - 1][c].rgbtGreen;
                totalBlue += image[r - 1][c].rgbtBlue;

            }
            // top row right col
            if (top && right)
            {
                cells++;
                totalRed += image[r - 1][c + 1].rgbtRed;
                totalGreen += image[r - 1][c + 1].rgbtGreen;
                totalBlue += image[r - 1][c + 1].rgbtBlue;
            }
            // same row left col
            if (left)
            {
                cells++;
                totalRed += image[r][c - 1].rgbtRed;
                totalGreen += image[r][c - 1].rgbtGreen;
                totalBlue += image[r][c - 1].rgbtBlue;
            }
            //same row right col
            if (right)
            {
                cells++;
                totalRed += image[r][c + 1].rgbtRed;
                totalGreen += image[r][c + 1].rgbtGreen;
                totalBlue += image[r][c + 1].rgbtBlue;
            }
            // bottom row left col
            if (bottom && left)
            {
                cells++;
                totalRed += image[r + 1][c - 1].rgbtRed;
                totalGreen += image[r + 1][c - 1].rgbtGreen;
                totalBlue += image[r + 1][c - 1].rgbtBlue;
            }
            // bottom row middle col
            if (bottom)
            {
                cells++;
                totalRed += image[r + 1][c].rgbtRed;
                totalGreen += image[r + 1][c].rgbtGreen;
                totalBlue += image[r + 1][c].rgbtBlue;

            }
            // bottom row right col
            if (bottom && right)
            {
                cells++;
                totalRed += image[r + 1][c + 1].rgbtRed;
                totalGreen += image[r + 1][c + 1].rgbtGreen;
                totalBlue += image[r + 1][c + 1].rgbtBlue;
            }
            int avgRed = round((float)totalRed / cells);
            int avgGreen = round((float)totalGreen / cells);
            int avgBlue = round((float)totalBlue / cells);

            blurred_img[r][c].rgbtRed = avgRed;
            blurred_img[r][c].rgbtGreen = avgGreen;
            blurred_img[r][c].rgbtBlue = avgBlue;

            // image[r][c].rgbtRed = avgRed;
            // image[r][c].rgbtGreen = avgGreen;
            // image[r][c].rgbtBlue = avgBlue;
        }
    }

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c].rgbtRed =  blurred_img[r][c].rgbtRed;
            image[r][c].rgbtGreen = blurred_img[r][c].rgbtGreen;
            image[r][c].rgbtBlue = blurred_img[r][c].rgbtBlue;
        }
    }
    return;
}
