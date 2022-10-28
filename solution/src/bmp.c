#include "bmp.h"

#pragma pack(push, 1)
struct bmp_header
{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)
/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* коды других ошибок  */
};

enum read_status from_bmp( FILE* in, struct image* img ){
    struct bmp_header bh;
    size_t count = fread(&bh, 1, sizeof(struct bmp_header), in);
    if (count != sizeof(struct bmp_header)){
        return READ_INVALID_HEADER;
    }
    struct image image;
    image.height = bh.biHeight;
    image.width = bh.biWidth;
    image.data = malloc(sizeof(struct pixel) * bh.biHeight * bh.biWidth);
    //int fs = fseek(in, bh.bOffBits, 0);
    int countRow = 0;
    int tmpwidth = image.width;
    int offset = 0;
    if ((tmpwidth * sizeof(struct pixel)) % 4 != 0){
        int needwidth = (int) tmpwidth * (int) sizeof(struct pixel);
        while (needwidth % 4 != 0){
            needwidth++;
        }

        offset = needwidth - (int) tmpwidth * (int) sizeof(struct pixel);

    }
    while (countRow < image.height){
        /*for (size_t i = 0; i < sizeof(image.data)/sizeof(*image.data); i++){
            printf("%u\n", (uint8_t)image.data[i].r);
        }*/
        count = fread(image.data+countRow*tmpwidth, 1,  tmpwidth * sizeof(struct pixel), in);
        //printf("%d\n", count);
        //printf("%d\n", tmpwidth);
        if (count != tmpwidth * sizeof(struct pixel)){
            return READ_INVALID_BITS;
        }
        fseek(in, offset, 1);
        countRow++;
    }

    *img = image;
    //free(image.data);
    return READ_OK;

}
void readfile(const char* fileName, struct image* img){
    FILE* file = fopen(fileName, "rb");
//    if (!file){
//        printf("File doesn't read\n");
//        exit(1);
//    }
    enum read_status rstatus = from_bmp(file, img);
    switch (rstatus){
        case READ_OK:{
            printf("Read's ok\n");
            break;
        }
        case READ_INVALID_SIGNATURE:{
            printf("Invalid signature\n");
            exit(1);
            break;
        }
        case READ_INVALID_BITS:{
            printf("Invalid bits\n");
            exit(1);
            break;
        }
        case READ_INVALID_HEADER:{
            printf("Check header\n");
            exit(1);
            break;
        }
        default:{
            printf("Unknown error");
            exit(1);
        }
    }
    fclose(file);
}
/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

enum write_status to_bmp( FILE* out, const struct image* img ){
    struct bmp_header bh;
    struct image image = *img;
    int tmpwidth = image.width;
    int padding = 0;
    if ((tmpwidth  * (int) sizeof(struct pixel)) % 4 != 0){
        int needwidth = (int) tmpwidth * (int) sizeof(struct pixel);
        while (needwidth % 4 != 0){
            needwidth++;
        }
        padding = needwidth - (int) tmpwidth * (int) sizeof(struct pixel);
    }
    int pixels_size = ((int) image.width * (int) sizeof(struct pixel) + padding)*(int)image.height;
    int file_size = (int) sizeof(struct bmp_header) + pixels_size;
    bh.bfType = 19778;
    bh.bfileSize = file_size;
    bh.bfReserved = 0;
    bh.bOffBits = 54;
    bh.biSize = 40;
    bh.biWidth = image.width;
    bh.biHeight = image.height;
    bh.biPlanes = 1;
    bh.biBitCount = 24;
    bh.biCompression = 0;
    bh.biSizeImage = pixels_size;
    bh.biXPelsPerMeter = 0;
    bh.biYPelsPerMeter = 0;
    bh.biClrUsed = 0;
    bh.biClrImportant = 0;
    size_t count = fwrite(&bh, 1,  sizeof(struct bmp_header), out);
    if (count != sizeof(struct bmp_header)){
        return WRITE_ERROR;
    }
    int countRow = 0;
    while (countRow < image.height){
        count = fwrite(image.data+countRow*tmpwidth, 1, tmpwidth * sizeof(struct pixel), out);
        if (count != tmpwidth * sizeof(struct pixel)){
            return WRITE_ERROR;
        }
        //fseek(out, padding, 1);
        for(int i = 0; i < padding;++i){
            uint8_t ccc = 0;
            fwrite(&ccc, 1, sizeof(uint8_t), out);
        }
        countRow++;
    }

    return WRITE_OK;
}
void writefile(const char* fileName, const struct image* image){
    FILE* file = fopen(fileName, "wb");
    if (!file){
        printf("File doesn't read\n");
        fclose(file);
        return;
    }
    enum write_status wstatus = to_bmp(file, image);
    switch (wstatus){
        case WRITE_OK:{
            printf("Write's ok\n");
            break;
        }
        case WRITE_ERROR:{
            printf("Write error\n");
            exit(1);
            break;
        }
        default:{
            printf("Unknown error");
            exit(1);
        }
    }
    fclose(file);
}
