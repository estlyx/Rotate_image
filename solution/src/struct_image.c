#include <stdint.h>
#include <malloc.h>

struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image new_img(uint64_t h, uint64_t w) {
    struct image image;
    image.height = h;
    image.width = w;
    image.data = malloc(sizeof(struct pixel) * h * w);
    return image;
}
