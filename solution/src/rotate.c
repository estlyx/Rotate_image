#include <malloc.h>
#include <stdio.h>
#include "struct_image.h"
struct image rotate( struct image const source ){
    struct image newimg = create();
    int w = source.width;
    int h = source.height;
    newimg.height = w;
    newimg.width = h;
    newimg.data = malloc(sizeof(struct pixel*) * w * h);
    //printf("%zu\n", sizeof(struct pixel));
    //printf("%zu\n", sizeof(newimg.data));
    //printf("%zu\n", sizeof(source.data));

    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            //newimg.data[(w - j - 1) * h + i] = source.data[i * w + j];
            newimg.data[(h - i - 1)+h*j] = source.data[i*w + j];
            //printf("%d %d\n", i, j);
        }
    }
    return newimg;
}