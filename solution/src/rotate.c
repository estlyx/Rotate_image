#include "rotate.h"
#include "struct_image.h"

int get_address( struct image const* source, size_t i, size_t j){
    int h = source->height;
    int address = (h - i - 1)+h*j;
    return address;
}

struct image new_img_rotate(struct image const* source){
    struct image newimg;
    int w = source->width;
    int h = source->height;
    newimg.height = w;
    newimg.width = h;
    newimg.data = malloc(sizeof(struct pixel) * w * h);
    return newimg;
}
struct image rotate( struct image const* source ){
    struct image newimg = new_img_rotate(source);
    int w = source->width;
    int h = source->height;

    for (size_t i = 0; i < h; i++){
        for (size_t j = 0; j < w; j++){
            newimg.data[get_address(source, i, j)] = source->data[i*w + j];
        }
    }
    return newimg;
}
