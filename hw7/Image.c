#include "Image.h"
#include <assert.h>
#include <stdlib.h>

/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    return image->R[y * image->W + x];
}

/* Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    return image->G[y * image->W + x];
}

/* Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    return image->B[y * image->W + x];
}

/* Set the color intensity of the Red channel of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r) {
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    image->R[y * image->W + x] = r;
}

/* Set the color intensity of the Green channel of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g) {
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    image->G[y * image->W + x] = g;
}

/* Set the color intensity of the Blue channel of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b) {
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    image->B[y * image->W + x] = b;
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image) {
    assert(image != NULL);
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image) {
    assert(image != NULL);
    return image->H;
}

/* Allocate the memory space for the image structure and the memory spaces for the color intensity values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height) {
    IMAGE *image = malloc(sizeof(IMAGE));
    assert(image != NULL);

    image->W = Width;
    image->H = Height;

    image->R = malloc(sizeof(unsigned char) * Width * Height);
    assert(image->R != NULL);

    image->G = malloc(sizeof(unsigned char) * Width * Height);
    assert(image->G != NULL);

    image->B = malloc(sizeof(unsigned char) * Width * Height);
    assert(image->B != NULL);

    return image;
}

/* Release the memory spaces for the pixel color intensity values */
/* Deallocate all the memory spaces for the image */
/* Set R/G/B pointers to NULL */
/* Deallocate all the memory spaces for the image */
/* Set R/G/B pointers to NULL */
void DeleteImage(IMAGE *image) {
    if (image == NULL) return;
    
    free(image->R);
    free(image->G);
    free(image->B);
    
    image->R = NULL;
    image->G = NULL;
    image->B = NULL;
    
    free(image);
}


