#include <stdio.h>
#include <stdlib.h> 
#include <strings.h>
#include <math.h> 
#include "lodepng.h" 

// принимаем на вход: имя файла, указатели на int для хранения прочитанной ширины и высоты картинки
// возвращаем указатель на выделенную память для хранения картинки
// Если память выделить не смогли, отдаем нулевой указатель и пишем сообщение об ошибке
unsigned char* load_png(const char* filename, unsigned int* width, unsigned int* height) 
{
  unsigned char* image = NULL; 
  int error = lodepng_decode32_file(&image, width, height, filename);
  if(error != 0) {
    printf("error %u: %s\n", error, lodepng_error_text(error)); 
  }
  return (image);
}

// принимаем на вход: имя файла для записи, указатель на массив пикселей,  ширину и высоту картинки
// Если преобразовать массив в картинку или сохранить не смогли,  пишем сообщение об ошибке
void write_png(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  unsigned char* png;
  //long unsigned int pngsize;
  size_t pngsize;
  int error = lodepng_encode32(&png, &pngsize, image, width, height);
  if(error == 0) {
      lodepng_save_file(png, pngsize, filename);
  } else { 
    printf("error %u: %s\n", error, lodepng_error_text(error));
  }
  free(png);
}


// вариант огрубления серого цвета в ЧБ 
void contrast(unsigned char *col, int bw_size)
{ 
    int i; 
    for(i=0; i < bw_size; i++)
    {
        if(col[i] < 55) col[i] = 0;
        if(col[i] > 195) col[i] = 255;
    } 
    return; 
} 

// Гауссово размыттие
void Gauss_blur(unsigned char *col, unsigned char *blr_pic, int width, int height)
{ 
    int i, j; 
    for(i=1; i < height-1; i++) 
        for(j=1; j < width-1; j++)
        { 
            blr_pic[width*i+j] = 0.084*col[width*i+j] + 0.084*col[width*(i+1)+j] + 0.084*col[width*(i-1)+j]; 
            blr_pic[width*i+j] = blr_pic[width*i+j] + 0.084*col[width*i+(j+1)] + 0.084*col[width*i+(j-1)]; 
            blr_pic[width*i+j] = blr_pic[width*i+j] + 0.063*col[width*(i+1)+(j+1)] + 0.063*col[width*(i+1)+(j-1)]; 
            blr_pic[width*i+j] = blr_pic[width*i+j] + 0.063*col[width*(i-1)+(j+1)] + 0.063*col[width*(i-1)+(j-1)]; 
        } 
   return; 
} 

//  Место для экспериментов
void color(unsigned char *blr_pic, unsigned char *res, int size)
{ 
    //int i;
    //for(i= 1;i<size;i++) 
    //{ 
    //    res[i*4]=40+blr_pic[i]+0.35*blr_pic[i-1]; 
    //    res[i*4+1]=65+blr_pic[i]; 
    //    res[i*4+2]=170+blr_pic[i]; 
    //    res[i*4+3]=255;
    //}
    for (int i = 0; i < size; i++) {
        res[i*4]=170+blr_pic[i];
        res[i*4+1]=170+blr_pic[i]; 
        res[i*4+2]=170+blr_pic[i]; 
        res[i*4+3]=255;
    }

    return; 
} 

//МОЯ ЧАСТЬ КОДА
void black_and_white(unsigned char *blr_pic, unsigned char *res, int size) {
    for (int i = 0; i < size; i++) {

        for (int k = 0; k < 3; k++) {
            if (res[i*4 + k] > 190) {
                res[i*4 + k] = 255;
            } else {
                res[i*4 + k] = 0;
            }
        }
    }
}
//МОЯ ЧАСТЬ КОДА

int main() 
{ 
    const char* filename = "Picture.png"; 
    unsigned int width, height;
    int size;
    int bw_size;
    
    // Прочитали картинку
    unsigned char* picture = load_png("Picture.png", &width, &height); 
    if (picture == NULL)
    { 
        printf("Problem reading picture from the file %s. Error.\n", filename); 
        return -1; 
    } 

    size = width * height * 4;
    bw_size = width * height;
    
    
    unsigned char* bw_pic = (unsigned char*)malloc(bw_size*sizeof(unsigned char)); 
    unsigned char* blr_pic = (unsigned char*)malloc(bw_size*sizeof(unsigned char)); 
    unsigned char* finish = (unsigned char*)malloc(size*sizeof(unsigned char)); 
    
    //МОЯ ЧАСТЬ КОДА
    for (int i = 0; i < bw_size; i++) {
        bw_pic[i] = picture[i * 4];
    }
    //МОЯ ЧАСТЬ КОДА

    // поиграли с Гауссом
    Gauss_blur(bw_pic, blr_pic, width, height); 

    //МОЯ ЧАСТЬ КОДА
    color(blr_pic, finish, bw_size);
    //МОЯ ЧАСТЬ КОДА
    // посмотрим на промежуточные картинки
    write_png("gauss.png", finish, width, height);
    

    
    // Например, поиграли с  контрастом
    contrast(bw_pic, bw_size);

    //МОЯ ЧАСТЬ КОДА
    color(blr_pic, finish, bw_size);
    //МОЯ ЧАСТЬ КОДА
    // посмотрим на промежуточные картинки
    write_png("contrast.png", finish, width, height);
    // сделали еще что-нибудь
    // .....
    // ....
    // ....
    // ....
    // ....
    // ....
    // ....
    //
    
    write_png("intermediate_result.png", finish, width, height);
    color(blr_pic, finish, bw_size); 
    

    //МОЯ ЧАСТЬ КОДА
    black_and_white(blr_pic, finish, bw_size);
    //МОЯ ЧАСТЬ КОДА
    // выписали результат
    write_png("picture_out.png", finish, width, height); 
    
    // не забыли почистить память!
    free(bw_pic); 
    free(blr_pic); 
    free(finish); 
    free(picture); 
    
    return 0; 
}
