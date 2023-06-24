/*********************************************************************/
/* PhotoLab.c: Assignment 6 for CENG231, Spring 2023                 */
/* Prepared by Prof. Emad Arasteh Modified by Jaccob Mau             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** global definitions ***/
#define WIDTH  500		/* image width */
#define HEIGHT 281		/* image height */
#define SLEN    80		/* maximum length of file names */

/*** function declarations ***/

/* Load an image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], 
        unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], 
        unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Age the image */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT]);

/* Change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

/* Reverse the image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

/* Flip an image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

/* Mirror an image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

/* Sharpen an image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

/* exchange R and B color channels */
void ExRB(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
        unsigned char B[WIDTH][HEIGHT]);

/* [Bonus] Add salt-and-pepper noise to image */
void AddNoise(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
        unsigned char B[WIDTH][HEIGHT], int percentage);

/* [Bonus] Add a border to the image */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
		unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int bwidth);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], 
        unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    /* Initial description */
    printf("----------------------------------------------\n");
    printf("All DIP Operations:\n");
    printf("- Age the image\n");
    printf("- Change the color image to black and white\n");
    printf("- Make a negative of the image\n");
    printf("- Flip the image vertially\n");
    printf("- Mirror the image horizontally\n");
    printf("- Sharpen the image\n");
    printf("- Exchange the red and blue color channels\n");
    printf("- Add noise to the image\n");
    printf("- Add a border to the image\n");
    printf("----------------------------------------------\n");
    
    /* Please extend the AutoTest function for the other DIP operations */
    AutoTest(R, G, B);

    return 0;
}

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~ceng231/bin/pnmtojpeg.sh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

/* Example: age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	          B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
            R[x][y] = (unsigned char) (B[x][y]*1.6);
            G[x][y] = (unsigned char) (B[x][y]*1.6);
	    }
    }
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("wilson", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
    printf("Aging tested!\n\n");
    
    /* BlackNWhite Test */
    LoadImage("wilson", R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black & White tested!\n\n");
    
    /* Negative Test */
    LoadImage("wilson", R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
    printf("negative tested!\n\n");
    
    /* Flip Image Vertically Test */
    LoadImage("wilson", R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    printf("Vertical Flip tested!\n\n");
    
    /* Mirror Test */
    LoadImage("wilson", R, G, B);
    HMirror(R, G, B);
    SaveImage("hmirror", R, G, B);
    printf("Mirror horizontally tested!\n\n");
    
    /* Sharpen Test */
    LoadImage("wilson", R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");
    
    /* Exchange RB Test */
    LoadImage("wilson", R, G, B);
    ExRB(R, G, B);
    SaveImage("xRB", R, G, B);
    printf("Exchange RB tested!\n\n");
    
    /* Noise Test */
    LoadImage("wilson", R, G, B);
    AddNoise(R, G, B, 20);
    SaveImage("noise", R, G, B);
    printf("AddNoise tested!\n\n");
    
    /* Boarders Test */
    LoadImage("wilson", R, G, B);
    AddBorder(R, G, B, 0, 0, 0, 20);
    SaveImage("border", R, G, B);
    printf("AddBorder tested!\n\n");
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/

/* Change a color image to black and white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    /* Initial variables */
    int x, y;
    
    /* Iterate through each pixel and change the value to an intensity */
    for (x = 0; x < HEIGHT; x++) {
        for (y = 0; y < WIDTH; y++) {
            int intensity = (R[y][x] + G[y][x] + B[y][x]) / 3;
            R[y][x] = G[y][x] = B[y][x] = (unsigned char)intensity;
        }
    }
}

/* Reverse the image color */
void Negative(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT])
{
    /* Initial variables */
    int x, y;
    
    /* Iterate throug hand use saturation equation for each RGB pixel */
    for (x = 0; x < HEIGHT; x++) {
        for (y = 0; y < WIDTH; y++) {
            R[y][x] = 255 - R[y][x];
            G[y][x] = 255 - G[y][x];
            B[y][x] = 255 - B[y][x];
        }
    }
}

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    /* Initial variables */
    int x, y;
    unsigned char temp;
    
    /* Iterate through each pixel */
    for (x = 0; x < HEIGHT/2; x++) {
        for (y = 0; y < WIDTH; y++) {
        
            /* Swap RGB values of two rows */
            temp = R[y][x];
            R[y][x] = R[y][HEIGHT-1-x];
            R[y][HEIGHT-1-x] = temp;

            temp = G[y][x];
            G[y][x] = G[y][HEIGHT-1-x];
            G[y][HEIGHT-1-x] = temp;

            temp = B[y][x];
            B[y][x] = B[y][HEIGHT-1-x];
            B[y][HEIGHT-1-x] = temp;
        }
    }
}

/* Mirror an image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    /* Initial variables */
    int x, y;
    
    /* Initial variables */
    for (x = 0; x < WIDTH/2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            int right_x = WIDTH - 1 - x;
            
            /* Initial variables */
            R[right_x][y] = R[x][y];
            G[right_x][y] = G[x][y];
            B[right_x][y] = B[x][y];
        }
    }
}

/* Sharpen an image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) 
{
    /* Initial variables */
    int i, j, x, y;
    int temp_R, temp_G, temp_B;
    unsigned char copy_G[WIDTH][HEIGHT], copy_B[WIDTH][HEIGHT], copy_R[WIDTH][HEIGHT];
    
    /* Iterate through each pixel */
    for (i = 1; i < WIDTH - 1; i++) {
        for (j = 1; j < HEIGHT - 1; j++) {
            
            /* Calculate pixel saturation value and set temp value */
            temp_R = -R[i-1][j-1] - R[i-1][j] - R[i-1][j+1] - R[i][j-1] + 9*R[i][j] - R[i][j+1] - R[i+1][j-1] - R[i+1][j] - R[i+1][j+1];
            temp_G = -G[i-1][j-1] - G[i-1][j] - G[i-1][j+1] - G[i][j-1] + 9*G[i][j] - G[i][j+1] - G[i+1][j-1] - G[i+1][j] - G[i+1][j+1];
            temp_B = -B[i-1][j-1] - B[i-1][j] - B[i-1][j+1] - B[i][j-1] + 9*B[i][j] - B[i][j+1] - B[i+1][j-1] - B[i+1][j] - B[i+1][j+1];

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
            R[x][y] = copy_R[x][y];
            G[x][y] = copy_G[x][y];
            B[x][y] = copy_B[x][y];
        }
    }
}


/* Exchange R and B color channels */
void ExRB(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    /* Initial variables */ 
    int x,y;
    unsigned char temp;
    
    /* Iterate and change R and B values */
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            temp = R[x][y];
            R[x][y] = B[x][y];
            B[x][y] = temp;
        }
    }
}

/* Add noise to an image */
void AddNoise(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int percentage)
{
    /* Initial variables */
    int n, x, y, i, value;
    
    /* Calculate number of pixels to iterate through*/
    n = percentage * WIDTH * HEIGHT / 100;
    
    /* Iterate through number of pixels and randomly pick and change each pixel */
    for (i = 0; i < n; i++) {
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        value = rand() % 2 == 0 ? 0 : 255;
        R[x][y] = G[x][y] = B[x][y] = value;
    }
}

/* Add a border to the image */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r, int g, int b, int bwidth) 
{    
    /* Initial variables */
    int x, y;
     
    /* Iterate over each pixel in the image */
    for (x = 0; x < WIDTH; x++) {
        for (y = 0; y < HEIGHT; y++) {
            /* If pixel is within the border width, set color to border color */
            if (x < bwidth || x >= WIDTH - bwidth || y < bwidth || y >= HEIGHT - bwidth) {
                R[x][y] = r;
                G[x][y] = g;
                B[x][y] = b;
            }
        }
    }
}


/* EOF */
