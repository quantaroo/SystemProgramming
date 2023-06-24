/*********************************************************************/
/* PhotoLab.c: Assignment 7 for CENG231, Spring 2023                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Image.h"

/*** global definitions ***/
#define SLEN      80		/* maximum length of file names */
#define MAX_PIXEL 255           /* maximum pixel intensity value */

/*** function declarations ***/
/* Read image from a file 						*/
/* The size of the image needs to be pre-set				*/
/* The memory spaces of the image will be allocated in this function	*/
/* Return values:							*/
/* NULL: fail to load or create an image				*/
/* image: load or create an image successfully				*/
IMAGE *LoadImage(const char *fname);

/* Save a processed image 		*/
/* Return values:			*/
/* 0: successfully saved the image	*/
/* 1: Cannot open the file for writing	*/
/* 2: File error while writing to file	*/
int SaveImage(const char *fname, const IMAGE *image);

/* Age the image */
IMAGE *Aging(IMAGE *image);

/* Black and White */
IMAGE *BlackNWhite(IMAGE *image);

/* Reverse image color */
IMAGE *Negative(IMAGE *image);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* exchange R and B color channels */
IMAGE *ExRB(IMAGE *image);

/* [Bonus] crop an image */
IMAGE *Crop(IMAGE *image, int X, int Y, int W, int H);

/* test all functions */
int AutoTest(void);

IMAGE *LoadImage(const char *fname)
{
	FILE         *File;
	char         Type[SLEN];
	int          W, H, MaxValue;
	unsigned int x, y;
	char         ftype[] = ".ppm";
	char         fname_tmp[SLEN];
	IMAGE        *image;
	strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);
	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("\nCan't open file \"%s\" for reading!\n", fname);
		return NULL;
	}

	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &W);
	if (W <= 0) {
		printf("\nUnsupported image width %d!\n", W);
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &H);
	if (H <= 0) {
		printf("\nUnsupported image height %d!\n", H);
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		fclose(File);
		return NULL;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected at the end of the file!\n");
		fclose(File);
		return NULL;
	}

	image = CreateImage(W, H);

	if (!image) {
		printf("\nError creating image from %s!\n", fname_tmp);
		fclose(File);
		return NULL;
	}
	else {
		for (y = 0; y < ImageHeight(image); y++)
			for (x = 0; x < ImageWidth(image); x++) {
				SetPixelR(image, x, y, fgetc(File));
				SetPixelG(image, x, y, fgetc(File));
				SetPixelB(image, x, y, fgetc(File));
			}

		if (ferror(File)) {
			printf("\nFile error while reading from file!\n");
			DeleteImage(image);
			return NULL;
		}

		printf("%s was read successfully!\n", fname_tmp);
		fclose(File);
		return image;
	}
}

int SaveImage(const char *fname, const IMAGE *image)
{
    assert(image != NULL && "No image to save!\n");
	FILE         *File;
	int          x, y;
	char         SysCmd[SLEN * 5];
	char         ftype[] = ".ppm";
	char         fname_tmp[SLEN];
	char         fname_tmp2[SLEN];
	unsigned int WIDTH = ImageWidth(image);
	unsigned int HEIGHT = ImageHeight(image);
	strcpy(fname_tmp, fname);
	strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("\nCan't open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(GetPixelR(image, x, y), File);
			fputc(GetPixelG(image, x, y), File);
			fputc(GetPixelB(image, x, y), File);
		}

	if (ferror(File)) {
		printf("\nError while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);
	/*
	 * Rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "~ceng231/bin/pnmtojpeg.sh %s",
			fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);
	return 0;
}

/* auto test */
int AutoTest(void) {
    int result;
    const char fname[SLEN] = "wilson";

	IMAGE *image = NULL;
    image = LoadImage(fname);
    if (! image) return 11;
    image = Aging(image);
    if (! image) return 12;
    result = SaveImage("aging", image);
    if (result) return result;
    printf("Aging tested!\n\n");
	  DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 13;
    image = BlackNWhite(image);
    if (! image) return 14;
    result = SaveImage("bw", image);
    if (result) return result;
    printf("Black and White tested!\n\n");
	  DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 15;
    image = Negative(image);
    if (! image) return 16;
    result = SaveImage("negative", image);
    if (result) return result;
    printf("Negative tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 17;
    image = VFlip(image);
    if (! image) return 18;
    result = SaveImage("vflip", image);
    if (result) return result;
    printf("VFlip tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 19;
    image = HMirror(image);
    if (! image) return 20;
    result = SaveImage("hmirror", image);
    if (result) return result;
    printf("HMirror tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 21;
    image = Sharpen(image);
    if (! image) return 22;
    result = SaveImage("sharpen", image);
    if (result) return result;
    printf("Sharpen tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = ExRB(image);
    if (! image) return 24;
    result = SaveImage("xRB", image);
    if (result) return result;
    printf("ExRB tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = Crop(image, 200, 150, 115, 130);
    if (! image) return 26;
    result = SaveImage("Crop", image);
    if (result) return result;
    printf("Crop tested!\n\n");
    DeleteImage(image);
	image = NULL;
    return 0; /* success! */
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/

IMAGE *Aging(IMAGE *image) {
  unsigned int x, y;
  for (y = 0; y < ImageHeight(image); y++) {
    for (x = 0; x < ImageWidth(image); x++) {
        unsigned char b = GetPixelB(image, x, y);
        unsigned char g = GetPixelG(image, x, y);
        unsigned char r = GetPixelR(image, x, y);
        SetPixelB(image, x, y, (r+g+b)/5);
        SetPixelR(image, x, y, (unsigned char)((r+g+b)*1.6/5));
        SetPixelG(image, x, y, (unsigned char)((r+g+b)*1.6/5));
    }
  }
  return image;
}

IMAGE *BlackNWhite(IMAGE *image) {
    /* Initial variables */
    int x, y;
    unsigned char intensity;

    /* Iterate through each pixel and change the value to an intensity */
    for (x = 0; x < image->H; x++) {
        for (y = 0; y < image->W; y++) {
            intensity = (unsigned char)((GetPixelR(image, y, x) + GetPixelG(image, y, x) + GetPixelB(image, y, x)) / 3);
            SetPixelR(image, y, x, intensity);
            SetPixelG(image, y, x, intensity);
            SetPixelB(image, y, x, intensity);
        }
    }
    return image;
}

IMAGE* Negative(IMAGE* image)
{
    /* Initial variables */
    unsigned int x, y;
    unsigned char r, g, b;
    
    /* Iterate through each pixel and apply the negative transformation */
    for (y = 0; y < image->H; y++) {
        for (x = 0; x < image->W; x++) {
            r = 255 - GetPixelR(image, x, y);
            g = 255 - GetPixelG(image, x, y);
            b = 255 - GetPixelB(image, x, y);
            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
        }
    }
    return image;
}

/* flip image vertically */
IMAGE *VFlip(IMAGE *image)
{
    /* Initial variables */
    int x, y;
    unsigned char temp;

    /* Iterate through each pixel */
    for (x = 0; x < ImageHeight(image)/2; x++) {
        for (y = 0; y < ImageWidth(image); y++) {

            /* Swap RGB values of two rows */
            temp = GetPixelR(image, y, x);
            SetPixelR(image, y, x, GetPixelR(image, y, ImageHeight(image)-1-x));
            SetPixelR(image, y, ImageHeight(image)-1-x, temp);

            temp = GetPixelG(image, y, x);
            SetPixelG(image, y, x, GetPixelG(image, y, ImageHeight(image)-1-x));
            SetPixelG(image, y, ImageHeight(image)-1-x, temp);

            temp = GetPixelB(image, y, x);
            SetPixelB(image, y, x, GetPixelB(image, y, ImageHeight(image)-1-x));
            SetPixelB(image, y, ImageHeight(image)-1-x, temp);
        }
    }
    return image;
}


IMAGE *HMirror(IMAGE *image)
{
    assert(image != NULL);
    
    unsigned int width = ImageWidth(image);
    unsigned int height = ImageHeight(image);
    
    unsigned int x,y;
    for (x = 0; x < width/2; x++) {
        for (y = 0; y < height; y++) {
            unsigned int right_x = width - 1 - x;
            
            unsigned char R_left = GetPixelR(image, x, y);
            unsigned char G_left = GetPixelG(image, x, y);
            unsigned char B_left = GetPixelB(image, x, y);
            
            SetPixelR(image, right_x, y, R_left);
            SetPixelG(image, right_x, y, G_left);
            SetPixelB(image, right_x, y, B_left);
        }
    }
    return image;
}


IMAGE *Sharpen(IMAGE *image) 
{
    /* Initial variables */
    int i, j, x, y;
    int temp_R, temp_G, temp_B;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);
    unsigned char copy_G[WIDTH][HEIGHT], copy_B[WIDTH][HEIGHT], copy_R[WIDTH][HEIGHT];
    
    /* Iterate through each pixel */
    for (i = 1; i < WIDTH - 1; i++) {
        for (j = 1; j < HEIGHT - 1; j++) {
            
            /* Calculate pixel saturation value and set temp value */
              temp_R = -GetPixelR(image, i-1, j-1) - GetPixelR(image, i-1, j) - GetPixelR(image, i-1, j+1) - GetPixelR(image, i, j-1) + 9*GetPixelR(image, i, j) - GetPixelR(image, i, j+1) - GetPixelR(image, i+1, j-1) - GetPixelR(image, i+1, j) - GetPixelR(image, i+1, j+1);
              temp_G = -GetPixelG(image, i-1, j-1) - GetPixelG(image, i-1, j) - GetPixelG(image, i-1, j+1) - GetPixelG(image, i, j-1) + 9*GetPixelG(image, i, j) - GetPixelG(image, i, j+1) - GetPixelG(image, i+1, j-1) - GetPixelG(image, i+1, j) - GetPixelG(image, i+1, j+1);
              temp_B = -GetPixelB(image, i-1, j-1) - GetPixelB(image, i-1, j) - GetPixelB(image, i-1, j+1) - GetPixelB(image, i, j-1) + 9*GetPixelB(image, i, j) - GetPixelB(image, i, j+1) - GetPixelB(image, i+1, j-1) - GetPixelB(image, i+1, j) - GetPixelB(image, i+1, j+1);



            /* Check and change each value if above 255 or below 0 */
            temp_R = (temp_R > 255) ? 255 : ((temp_R < 0) ? 0 : temp_R);
            temp_G = (temp_G > 255) ? 255 : ((temp_G < 0) ? 0 : temp_G);
            temp_B = (temp_B > 255) ? 255 : ((temp_B < 0) ? 0 : temp_B);

            /* Change value to unsigned char value into copy array */
            copy_R[i][j] = (unsigned char)temp_R;
            copy_G[i][j] = (unsigned char)temp_G;
            copy_B[i][j] = (unsigned char)temp_B;
        }
    }
    
    /* Iterate through and set copy array to set array */
    for (x = 0; x < WIDTH; x++) {
        for (y = 0; y < HEIGHT; y++) {
            SetPixelR(image,x,y,copy_R[x][y]);
            SetPixelG(image,x,y,copy_G[x][y]);
            SetPixelB(image,x,y,copy_B[x][y]);
        }
    }
    return image;
    
}





/* Exchange R and B color channels of image */
IMAGE *ExRB(IMAGE *image)
{
    assert(image != NULL);
    
    /* Initial variables */ 
    int x, y;
    unsigned char temp;
    
    /* Iterate and change R and B values */
    for (y = 0; y < ImageHeight(image); y++) {
         for (x = 0; x < ImageWidth(image); x++) {
            temp = GetPixelR(image, x, y);
            SetPixelR(image, x, y, GetPixelB(image, x, y));
            SetPixelB(image, x, y, temp);
        }
    }
    
    return image;
}


IMAGE *Crop(IMAGE *image, int x, int y, int W, int H)
{
    assert(image != NULL);

    int originalWidth = ImageWidth(image);
    int originalHeight = ImageHeight(image);

    int cropWidth = (W + x > originalWidth) ? (originalWidth - x) : W;
    int cropHeight = (H + y > originalHeight) ? (originalHeight - y) : H;


    int newX, newY;
    for (newY = 0; newY < originalHeight; newY++) {
        for (newX = 0; newX < originalWidth; newX++) {
            if((newY<=cropHeight)&&(newX<=cropWidth)){
              SetPixelR(image, newX, newY, GetPixelR(image, x + newX, y + newY));
              SetPixelG(image, newX, newY, GetPixelG(image, x + newX, y + newY));
              SetPixelB(image, newX, newY, GetPixelB(image, x + newX, y + newY));
            }
            else{
              SetPixelR(image, newX, newY, 0);
              SetPixelG(image, newX, newY, 0);
              SetPixelB(image, newX, newY, 0);
            }
        }
    }

    return image;
}


/**************************************************************/
/* Main function (do not modify!)                             */
/**************************************************************/

int main(void)
{
  int result;
  result = AutoTest();
  if (result) {
	printf("AutoTest failed, error code %d!\n", result);
  }
  else{
	printf("AutoTest finished.\n");
  }
  return 0;
}
