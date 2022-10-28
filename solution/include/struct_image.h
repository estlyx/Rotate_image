#ifndef IMAGE_HEADER_FILE
#define IMAGE_HEADER_FILE
#include <stdint.h>
#pragma pack(push, 1)
struct pixel {
    uint8_t b, g, r;
};
#pragma pack(pop)

struct image {
    uint64_t width, height;
    struct pixel* data
};
#endif
