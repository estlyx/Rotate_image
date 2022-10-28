#include <stdio.h>
#include "bmp.h"
#include "rotate.h"
//#include "struct_image.h"

int main(int argc, char** argv) {
    //struct image img = readfile("C:\\Users\\user\\CLionProjects\\assignment-image-rotation\\tester\\tests\\1\\input.bmp");
    if (argc != 3){
        printf("Wrong arguments");
        return 1;
    }
    struct image img = readfile(argv[1]);
    //C:\Users\user\CLionProjects\untitled\wlop-43se.bmp
    //C:\Users\user\CLionProjects\assignment-image-rotation\tester\tests\1\input.bmp
    struct image newimg = rotate(img);
    //for(int lol = 0; lol < 2; ++lol)
    //    newimg = rotate(newimg);
    free(img.data);
    //writefile("C:\\Users\\user\\CLionProjects\\assignment-image-rotation\\tester\\tests\\1\\output.bmp", &newimg);
    writefile(argv[2], &newimg);
    //open file(fopen->FILE)
    //from_bmp(FILE)->image
    //fclose
    //rotate(image)
    //write(image)
        //fopen
        //to_bmp(FILE)
    //fclose
    //printf("Hello, World!\n");
    return 0;
}
