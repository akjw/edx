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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // init algorithm matrix
    int GX[3][3] =
    {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };

    int GY[3][3] =
    {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int grid_row[] = {row - 1, row, row + 1};
            int grid_col[] = {col - 1, col, col + 1};
            float gx_red = 0, gx_green = 0, gx_blue = 0;
            float gy_red = 0, gy_green = 0, gy_blue = 0;

            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int current_row = grid_row[r];
                    int current_col = grid_col[c];

                    if (current_row >= 0 && current_row < height && current_col >= 0 && current_col < width)
                    {
                        RGBTRIPLE pixel = image[current_row][current_col];

                        gx_red += GX[r][c] * pixel.rgbtRed;
                        gx_green += GX[r][c] * pixel.rgbtGreen;
                        gx_blue += GX[r][c] * pixel.rgbtBlue;

                        gy_red += GY[r][c] * pixel.rgbtRed;
                        gy_green += GY[r][c] * pixel.rgbtGreen;
                        gy_blue += GY[r][c] * pixel.rgbtBlue;
                    }
                }
            }

            // square root

            int newR = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int newG = round(sqrt(gx_green * gx_green  + gy_green  * gy_green));
            int newB = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            temp[row][col].rgbtRed = newR > 255 ? 255 : newR;
            temp[row][col].rgbtGreen = newG > 255 ? 255 : newG;
            temp[row][col].rgbtBlue = newB > 255 ? 255 : newB;
        }
    }

    // Copy to new image
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c] =  temp[r][c];
        }
    }
    return;
}
