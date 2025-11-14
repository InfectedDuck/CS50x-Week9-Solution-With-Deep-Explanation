#include "helpers.h" // Includes the custom header file which likely defines the RGBTRIPLE structure and function prototypes.
#include <math.h>    // Includes the mathematical functions library, used for mathematical operations such as rounding and square root calculations.

// Convert image to grayscale
// Converts each pixel of the image to grayscale by averaging its red, green, and blue color values.
// This is done by setting all color channels to the average value, resulting in a monochromatic image.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column of the image
        for (int j = 0; j < width; j++)
        {
            // Compute the average of the red, green, and blue components for the current pixel.
            // (Note: Using `3.0` ensures floating-point division for accurate averaging.)
            int mid_value = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            
            // Set the red, green, and blue components of the current pixel to the computed average value.
            // This effectively converts the pixel to grayscale.
            image[i][j].rgbtRed = mid_value;
            image[i][j].rgbtBlue = mid_value;
            image[i][j].rgbtGreen = mid_value;
        }
    }
}

// Reflect image horizontally
// Mirrors the image horizontally by swapping pixels from the left side with those on the right side of each row.
// This operation creates a mirrored effect along the vertical axis.
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
// This operation smooths out transitions and reduces sharpness in the image.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to store original pixel values
    // This prevents modifying pixels while calculating the blur effect.
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

// Detect edges
// Applies an edge-detection filter to the image by computing gradients in the x and y directions.
// The gradients are calculated using convolution with Sobel operators, which highlight edges in the image.
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to store original pixel values
    // This prevents modifying pixels while calculating edge detection.
    RGBTRIPLE temp[height][width];

    // Define Sobel operators for edge detection in the x and y directions
    // These operators are used to compute the gradient of the image
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Copy the original image to the temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each column of the image
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to accumulate the gradients in the x and y directions for red, green, and blue components
            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

            // Iterate over the neighboring pixels within a 3x3 grid centered around the current pixel
            // Compute gradients by applying Sobel operators
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // Check if the neighboring pixel is within the image boundaries
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        // Compute gradient values for each color component
                        int weightX = gx[x - (i - 1)][y - (j - 1)];
                        int weightY = gy[x - (i - 1)][y - (j - 1)];
                        gxRed += temp[x][y].rgbtRed * weightX;
                        gxGreen += temp[x][y].rgbtGreen * weightX;
                        gxBlue += temp[x][y].rgbtBlue * weightX;
                        gyRed += temp[x][y].rgbtRed * weightY;
                        gyGreen += temp[x][y].rgbtGreen * weightY;
                        gyBlue += temp[x][y].rgbtBlue * weightY;
                    }
                }
            }

            // Compute the final gradient magnitude for each color component
            int finalRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int finalGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int finalBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // Clamp the gradient values to ensure they do not exceed the maximum allowed value of 255
            finalRed = finalRed > 255 ? 255 : finalRed;
            finalGreen = finalGreen > 255 ? 255 : finalGreen;
            finalBlue = finalBlue > 255 ? 255 : finalBlue;

            // Set the red, green, and blue components of the current pixel to the computed edge-detected values
            image[i][j].rgbtRed = finalRed;
            image[i][j].rgbtGreen = finalGreen;
            image[i][j].rgbtBlue = finalBlue;
        }
    }
}
