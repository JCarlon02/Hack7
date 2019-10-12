#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "imageUtils.h"

Pixel **loadImage(const char *filePath, int *height, int *width) {
  int x,y,n;
  unsigned char *data = stbi_load(filePath, &x, &y, &n, 4); //4 = force RGBA channels
  *height = y;
  *width = x;

  //contiguous allocation:
  Pixel **image = (Pixel **)malloc(sizeof(Pixel *) * y);
  image[0] = (Pixel *)malloc(sizeof(Pixel) * (y * x));
  for(int i=1; i<y; i++) {
    image[i] = (*image + (x * i));
  }

  int rowIndex = 0;
  int colIndex = 0;
  for(int i=0; i<(x * y * 4); i+=4) { //for each row
      image[rowIndex][colIndex].red   = data[i+0];
      image[rowIndex][colIndex].green = data[i+1];
      image[rowIndex][colIndex].blue  = data[i+2];
      colIndex++;
      if(colIndex == x) {
        //go to next row, reset column
        rowIndex++;
        colIndex=0;
      }
  }
  stbi_image_free(data);
  return image;
}

void saveImage(const char *fileName, Pixel **image, int height, int width) {

  // Convert height x width Pixel array to single array with
  // 3 (RGB) channels, ignoring the alpha channel and assume 100% opaque
  unsigned char *data = (unsigned char *) malloc(height * width * 3);
  int x = 0;
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      data[x+0] = image[i][j].red;
      data[x+1] = image[i][j].green;
      data[x+2] = image[i][j].blue;
      x+=3;
    }
  }
  //write
  stbi_write_jpg(fileName, width, height, 3, data, 100);
  free(data);
  return;
}

Pixel ** copyImage(Pixel **image, int height, int width) {
  Pixel ** copy = (Pixel **) malloc(sizeof(Pixel *) * height);
  int i;
  int j;
  for (i = 0; i < height; i++) {
    copy[i] = (Pixel *) malloc(sizeof(Pixel) * width);
  }
  for (i = 0; i < height; i++) {
    for(j = 0; j < width; j++){
      copy[i][j] = image[i][j];
    }
  }
  return copy;
}

void flipHorizontal(Pixel **image, int height, int width) {
int i;
int j;
Pixel temp;
for ( i = 0; i < width/2; i++) {
  for ( j = 0; j < height; j++) {
    temp = image[j][i];
    image[j][i] = image[j][width-1-i];
    image[j][width-1-i] = temp;
  }
}
  return;
}

void flipVertical(Pixel **image, int height, int width) {
  int i;
  Pixel *temp;
  for(i = 0; i < height/2; i++) {
    temp = image[i];
    image[i] = image[(height-1)-i];
    image[(height-1)-i] = temp;
  }
  return;
}

Pixel ** rotateClockwise(Pixel **image, int height, int width) {
  int i;
  int j;

  Pixel** clockwiseImage = (Pixel **) malloc(sizeof(Pixel *) * width);
  for (i = 0; i < width; i++) {
    clockwiseImage[i] = (Pixel *) malloc(sizeof(Pixel) * height);
  }

  for (i = 0; i < height; i++) {
    for(j = 0; j < width; j++){
      clockwiseImage[j][height-1-i] = image[i][j];
    }
  }

  return clockwiseImage;
}
