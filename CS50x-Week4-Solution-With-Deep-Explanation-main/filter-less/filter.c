#include <getopt.h>  // Includes the getopt library for command-line option parsing
#include <stdio.h>   // Includes the standard I/O library for file operations and printing
#include <stdlib.h>  // Includes the standard library for memory allocation and process control
#include <math.h>    // Includes the mathematical functions library for math operations

#include "helpers.h" // Includes the custom header file defining the BITMAPFILEHEADER, BITMAPINFOHEADER, RGBTRIPLE structures, and image processing functions

int main(int argc, char *argv[])
{
    // Define allowable filter options: b for blur, g for grayscale, r for reflect, s for sepia
    char *filters = "bgrs";

    // Get filter flag from command-line arguments
    char filter = getopt(argc, argv, filters);

    // Check if an invalid filter flag was provided
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;  // Exit with error code 1 for invalid filter
    }

    // Ensure that only one filter is specified
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;  // Exit with error code 2 for multiple filters
    }

    // Ensure proper usage of the program (i.e., exactly two additional arguments: infile and outfile)
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;  // Exit with error code 3 for incorrect usage
    }

    // Store input and output filenames from command-line arguments
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open the input file for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;  // Exit with error code 4 for failure to open input file
    }

    // Open the output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);  // Close input file if output file cannot be created
        printf("Could not create %s.\n", outfile);
        return 5;  // Exit with error code 5 for failure to create output file
    }

    // Read the BITMAPFILEHEADER from the input file
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read the BITMAPINFOHEADER from the input file
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Validate that the input file is a 24-bit uncompressed BMP file
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);  // Close output file
        fclose(inptr);   // Close input file
        printf("Unsupported file format.\n");
        return 6;  // Exit with error code 6 for unsupported file format
    }

    // Get image dimensions
    int height = abs(bi.biHeight);  // Height of the image (absolute value for BMP files where height is negative for top-down bitmaps)
    int width = bi.biWidth;         // Width of the image

    // Allocate memory for the image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);  // Close output file
        fclose(inptr);   // Close input file
        return 7;  // Exit with error code 7 for memory allocation failure
    }

    // Calculate padding for each row (rows must be aligned to 4-byte boundaries)
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Read the image's scanlines from the input file
    for (int i = 0; i < height; i++)
    {
        // Read one row of pixels into the image array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over the padding bytes at the end of the row
        fseek(inptr, padding, SEEK_CUR);
    }

    // Apply the selected filter to the image
    switch (filter)
    {
        // Apply blur filter
        case 'b':
            blur(height, width, image);
            break;

        // Apply grayscale filter
        case 'g':
            grayscale(height, width, image);
            break;

        // Apply reflection filter
        case 'r':
            reflect(height, width, image);
            break;

        // Apply sepia filter
        case 's':
            sepia(height, width, image);
            break;
    }

    // Write the BITMAPFILEHEADER to the output file
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write the BITMAPINFOHEADER to the output file
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write the modified image to the output file
    for (int i = 0; i < height; i++)
    {
        // Write one row of pixels to the output file
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding bytes at the end of the row to align with 4-byte boundaries
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free the allocated memory for the image
    free(image);

    // Close the input and output files
    fclose(inptr);
    fclose(outptr);
    
    return 0;  // Exit successfully
}
