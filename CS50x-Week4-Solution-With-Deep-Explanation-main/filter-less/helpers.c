#include "helpers.h"
#include <math.h>  // Library for mathematical functions like round()

// Convert image to grayscale
// Converts each pixel of the image to grayscale by averaging its red, green, and blue color values.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column of the image
        for (int j = 0; j < width; j++)
        {
            // Compute the average of the red, green, and blue components for the current pixel
            // (Note: Using `3.0` ensures floating-point division)
            int mid_value = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            
            // Set the red, green, and blue components of the current pixel to the computed average value
            // This effectively converts the pixel to grayscale
            image[i][j].rgbtRed = mid_value;
            image[i][j].rgbtBlue = mid_value;
            image[i][j].rgbtGreen = mid_value;
        }
    }
}

// Convert image to sepia
// Applies a sepia filter to the entire image to give it a warm, brownish tone.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column of the image
        for (int j = 0; j < width; j++)
        {
            // Retrieve the original red, green, and blue color values of the current pixel
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Apply the sepia filter formula to compute the new red, green, and blue values
            // The formula combines the original color components with fixed weights to achieve a sepia effect
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Clamp the sepia color values to ensure they do not exceed the maximum allowed value of 255
            // This prevents overflow and keeps the colors within the valid range
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            // Set the red, green, and blue components of the current pixel to the computed sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
// Mirrors the image horizontally by swapping pixels from the left side with those on the right side of each row.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Initialize two pointers for the start and end of the current row
        int start = 0;
        int end = width - 1;

        // Swap pixels from the start and end, moving towards the center of the row
        while (start < end)
        {
            // Temporarily store the pixel at the start position
            RGBTRIPLE temp = image[i][start];
            
            // Swap the pixel at the start position with the pixel at the end position
            image[i][start] = image[i][end];
            image[i][end] = temp;

            // Move the start pointer right and the end pointer left
            start++;
            end--;
        }
    }
}

// Blur image
// Applies a blur effect to the image by averaging the colors of neighboring pixels in a 3x3 grid.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to store original pixel values
    // This prevents modifying pixels while calculating the blur effect
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy each pixel from the original image to the temporary image
            temp[i][j] = image[i][j];
        }
    }

    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column of the image
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to accumulate the sum of color values and count the number of pixels considered
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate over the neighboring pixels within a 3x3 grid centered around the current pixel
            // This covers the pixel itself and its 8 neighbors
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // Check if the neighboring pixel is within the image boundaries
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        // Accumulate the color values of the neighboring pixel
                        sumRed += temp[x][y].rgbtRed;
                        sumGreen += temp[x][y].rgbtGreen;
                        sumBlue += temp[x][y].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average color values for the current pixel and update its color
            // Casting `count` to `float` ensures accurate division
            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }
}
