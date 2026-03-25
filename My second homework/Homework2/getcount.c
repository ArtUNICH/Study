#include <stdio.h>
#include <stdlib.h> 
#include <strings.h>
#include <math.h> 
#include "lodepng.h"

#include <stdio.h>
#include <stdlib.h>

unsigned char* load_png_main(const char* filename, unsigned int* width, unsigned int* height)
{
  unsigned char* image = NULL; 
  int error = lodepng_decode32_file(&image, width, height, filename);
  if(error != 0) {
    printf("error %u: %s\n", error, lodepng_error_text(error)); 
  }
  return image;
}

void DepthSearch(int** matrix, int** visited, int x, int y, unsigned int width, unsigned int height) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return;
    }
    visited[x][y] = 1;
    DepthSearch(matrix, visited, x + 1, y, width, height);
    DepthSearch(matrix, visited, x - 1, y, width, height);
    DepthSearch(matrix, visited, x, y + 1, width, height);
    DepthSearch(matrix, visited, x, y - 1, width, height);
}

int count_of_connecting_components(int** matrix, int** visited, unsigned int width, unsigned int height) {
    int count = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (matrix[i][j] == 1 && visited[i][j] == 0) {
                count++;
                DepthSearch(matrix, visited, i, j, width, height);
            }
        }
    }
    return count;
}

int** create_matrix_of_pixels(unsigned char* picture, unsigned int width, unsigned int height) {
    int** matrix_of_pixels = (int**)malloc(width * sizeof(int*));
    for (int h = 0; h < height; h++) {
        matrix_of_pixels[h] = (int*)malloc(width * sizeof(int));
        for (int w = 0; w < width; w++) {
            int k = (h * width + w) * 4;
            if (picture[k] == 255 && picture[k + 1] == 255 && picture[k + 2] == 255) {
                matrix_of_pixels[h][w] = 1;
            } else {
                matrix_of_pixels[h][w] = 0;
            }
        }
    }
    return matrix_of_pixels;
}


int main() 
{
    unsigned char* filename = "picture_out.png";
    unsigned int width, height;
    
    unsigned char* picture = load_png_main(filename, &width, &height);
    if (picture == NULL)
    { 
        printf("Problem reading picture from the file %s. Error.\n", filename); 
        return -1; 
    }

    int** matrix_of_pixels = create_matrix_of_pixels(picture, width, height);
    int** visited = (int**)malloc(width * sizeof(int*));
    for (int h = 0; h < height; h++) {
        visited[h] = (int*)calloc(width, sizeof(int));
    }

    int count_of_conecting_components = count_of_connecting_components(matrix_of_pixels, visited, width, height);
    printf("COUNT = %d\n", count_of_conecting_components);

    free(matrix_of_pixels);
    return 0;
}