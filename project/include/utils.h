//
// Created by steve on 27.10.2020.
//

#ifndef IZ2_UTILS_H
#define IZ2_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <time.h>
#include <sys/time.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_SIZE_T_LENGTH 5
#define MAX_INT_LENGTH 10
#define FAILURE 1
#define SUCCESS 0

typedef struct {
    int* temperature_array;
    size_t arr_size;
} From_file;

int get_arr_size(FILE* ptr, size_t* arr_size);
int get_int(FILE* ptr);
From_file* read_file(const char* file_path);

#endif //IZ2_UTILS_H
