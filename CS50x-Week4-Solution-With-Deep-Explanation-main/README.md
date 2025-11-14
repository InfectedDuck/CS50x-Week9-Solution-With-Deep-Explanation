# README
### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains C programs for different tasks:

1. **Volume Adjustment**
   - `volume.c`: Adjusts the volume of audio samples in a file.
2. **Image Filtering**
   - `filter.c`: Applies various filters to BMP images.
   - `helpers.c` and `helpers.c`: Contains implementations of image filters.
   - `helpers.h`: Header file for helper functions.

## Volume Adjustment Project

### Overview

The `volume.c` program adjusts the volume of audio samples in a file by scaling their amplitude. This tool is useful for modifying the loudness of audio recordings.

### File: `volume.c`

**Purpose**

The `volume.c` program processes an audio file to increase or decrease its volume by applying a scaling factor to each audio sample.

**How it Works**

1. **File Handling**: Opens and reads the input audio file, expected to be in a specific format (e.g., WAV).
2. **Volume Adjustment**: Applies a volume adjustment factor to each audio sample. This factor acts as a multiplier to modify the amplitude of the audio signal.
3. **Output**: Writes the adjusted audio data to a new output file.

**Key Points**

- **Volume Scaling**: Uses a multiplier to adjust audio sample amplitude.
- **File Operations**: Handles reading and writing audio data, ensuring format correctness.

**Example**

To compile and run the program, use the following commands:
```bash
make volume
./volume input.wav output.wav 0.5
```

## Image Filtering Project

### Overview

This project involves implementing image filtering techniques for BMP files. The goal is to apply different filters to images, including grayscale, sepia, reflection, and blur.

## Files and Their Descriptions

### `filter.c`

**Purpose**

The `filter.c` program applies filters to BMP images based on user input. It reads an image file, processes it according to the chosen filter, and writes the modified image to a new file.

**How it Works**

- **Command-line Arguments**: Specifies the filter to apply (-b for blur, -g for grayscale, -r for reflection, -s for sepia) and the input and output file paths.
- **File Handling**: Opens the input BMP file, verifies that it is a BMP file, and reads the image data into a 2D array.
- **Filter Application**: Calls the appropriate function from `helpers1.c` or `helpers2.c`.
- **Output**: Writes the processed image to the output file.

**Key Points**

- **Command-line Interface**: Provides flexibility to apply different filters.
- **File Operations**: Ensures correct handling of BMP file format and metadata.

### `helpers.c`

**Purpose**

The `helpers1.c` file contains implementations of specific image filters.

**Functions**

- **Grayscale**: Converts an image to grayscale by averaging the red, green, and blue values of each pixel.
- **Sepia**: Applies a sepia tone to an image by adjusting the red, green, and blue values to give a vintage effect.
- **Reflection**: Reflects the image horizontally, creating a mirror image of the original.

**Key Points**

- **Image Manipulation**: Implements basic image processing techniques.
- **Filter Functions**: Modular approach to applying different filters.

### `helpers.c`

**Purpose**

The `helpers2.c` file contains implementations of additional image filters.

**Functions**

- **Blur**: Applies a box blur to the image by averaging the pixel values in a defined box around each pixel.
- **Additional Filters**: Includes extra filtering methods not present in `helpers1.c`.

**Key Points**

- **Advanced Filtering**: Handles more complex image manipulation.
- **Modularity**: Separates different filtering methods into different files.

### `helpers.h`

**Purpose**

The `helpers.h` header file provides function prototypes for the helper functions defined in `helpers.c` and `helpers.c`.

**Key Points**

- **Function Prototypes**: Declares the functions used for filtering images.
- **Consistency**: Ensures that the function signatures are consistent across different files.

## Credits

<table>
  <tr>
    <td><img src="images/CS50x_logo.png" alt="CS50 Logo" width="800" height="300"></td>
    <td>
      <h3>Credits to CS50x</h3>
      <p>This project was inspired by and developed as part of the CS50x course offered by Harvard University. CS50x is an introduction to the intellectual enterprises of computer science and the art of programming.</p>
      <ul>
        <li><strong>Course:</strong> CS50x: Introduction to Computer Science</li>
        <li><strong>Institution:</strong> Harvard University</li>
        <li><strong>Instructor:</strong> David J. Malan</li>
        <li><strong>Website:</strong> <a href="https://cs50.harvard.edu/x/2024/">CS50x Official Site</a></li>
      </ul>
      <p>Thank you to the CS50x team for providing such a comprehensive and engaging introduction to computer science.</p>
    </td>
  </tr>
</table>
