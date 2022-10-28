#include  <stdint.h>
#include <stdio.h>
#include "struct_image.h"
#include <stdlib.h>

struct image readfile(const char* fileName);
void writefile(const char* fileName, const struct image* image);
