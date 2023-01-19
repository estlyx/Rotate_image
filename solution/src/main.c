#include "bmp.h"
#include "rotate.h"

int main(int argc, char** argv) {
    if (argc != 3){
        printf("Wrong arguments");
        return 1;
    }
    struct image img;
    read_file(argv[1], &img);
    struct image newimg = rotate(&img);
    free(img.data);
    write_file(argv[2], &newimg);
    return 0;
}
