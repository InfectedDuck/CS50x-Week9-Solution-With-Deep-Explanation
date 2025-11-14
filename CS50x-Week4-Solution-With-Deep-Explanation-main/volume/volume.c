// Modifies the volume of an audio file

#include <stdint.h>  // For fixed-width integer types
#include <stdio.h>   // For file operations and standard I/O functions
#include <stdlib.h>  // For memory allocation and utility functions

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    // argc should be 4: program name, input file, output file, and volume factor
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;  // Exit with error code 1 for incorrect usage
    }

    // Open the input file for reading in binary mode
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;  // Exit with error code 1 for failure to open input file
    }

    // Open the output file for writing in binary mode
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input);  // Close input file if output file cannot be opened
        return 1;  // Exit with error code 1 for failure to open output file
    }

    // Get the volume scaling factor from command-line arguments
    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t buffer_data[HEADER_SIZE];  // Buffer to hold the header data
    fread(buffer_data, HEADER_SIZE, 1, input);  // Read header from input file
    fwrite(buffer_data, HEADER_SIZE, 1, output);  // Write header to output file

    // Read samples from input file, adjust volume, and write modified samples to output file
    int16_t buffer_data_sample;  // Buffer to hold audio sample data
    while (fread(&buffer_data_sample, sizeof(int16_t), 1, input) == 1)
    {
        // Modify sample based on volume factor
        buffer_data_sample *= factor;

        // Write the modified sample to the output file
        fwrite(&buffer_data_sample, sizeof(int16_t), 1, output);
    }

    // Close the files
    fclose(input);
    fclose(output);

    return 0;  // Exit successfully
}
