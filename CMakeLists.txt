cmake_minimum_required(VERSION 3.23)
project(untitled C)

set(CMAKE_C_STANDARD 17)
set(SOURCE_FILES bmp.c bmp.h main.c rotate.c rotate.h struct_image.c struct_image.h)
add_executable(untitled ${SOURCE_FILES})
