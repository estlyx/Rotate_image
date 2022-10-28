#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};
struct image create(){
    //struct image* image = malloc(sizeof(struct image));
    // return *image;
    struct image image;
    return image;
}
