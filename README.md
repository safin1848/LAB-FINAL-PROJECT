IMAGE MANIPULATION SOFTWARE IN C
=================================

This project implements the required parts of the assignment.
The optional Sharpening feature is NOT included.

Required features included:
1. IUP GUI
2. Open 24-bit uncompressed BMP
3. Display image
4. Save 24-bit uncompressed BMP
5. Grayscale
6. Brightness adjustment
7. Image inversion
8. Horizontal flip
9. Vertical flip
10. Rotate 90 degrees clockwise
11. Crop
12. 3x3 blur
13. One-level Undo
14. Dynamic memory management
15. Error handling for common invalid cases

FILES
-----
main.c
    Starts IUP and opens the main window.

image.h / image.c
    Pixel/Image structures, allocation, copy, free,
    BMP loading and BMP saving.

processing.h / processing.c
    All required image manipulation algorithms.

gui.h / gui.c
    IUP window, buttons, file dialogs, text inputs,
    callbacks and image display.

IMPORTANT
---------
The assignment requires 24-bit uncompressed BMP only.
PNG/JPEG/GIF are not supported.

IUP DISPLAY
-----------
The GUI uses IupImageRGB() to display the RGB pixel buffer.
IupImageRGB duplicates the supplied pixel data internally.

BUILD
-----
You must have IUP installed and configured for your C compiler.

Linux/macOS:
Use the IUP compiler/linker flags supplied by your IUP installation.
If your installation provides pkg-config, a typical command is:

    gcc main.c gui.c image.c processing.c -o ImageEditor $(pkg-config --cflags --libs iup)

Windows/MinGW:
Add the IUP include directory and library directory to your compiler/project.
Then link the IUP library and the system libraries required by your
particular IUP package. The exact command depends on the IUP package
and MinGW version.

RUN
---
Run ImageEditor.
Click Open and select a 24-bit uncompressed .bmp file.

Brightness:
    Enter a positive integer to make the image brighter.
    Enter a negative integer to make it darker.

Crop:
    X and Y = starting coordinate
    W and H = crop width and height

Example:
    X=100, Y=50, W=300, H=200

VIVA POINTS
-----------
Pixel:
    unsigned char r, g, b

Image:
    int width, height
    Pixel *data

Pixel access:
    image->data[y * image->width + x]

The GUI callbacks call processing functions instead of putting
the complete image algorithms inside the callbacks.
