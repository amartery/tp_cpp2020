//
// Created by steve on 27.10.2020.
//
#include "utils.h"


int get_arr_size(FILE* ptr, size_t* arr_size) {
    if (ptr == NULL) {
        return FAILURE;
    }
    char buffer_arr_size[MAX_SIZE_T_LENGTH];
    int flag_input = fscanf(ptr, "%s", buffer_arr_size);
    if (flag_input == -1) {
        return FAILURE;
    } else {
        *arr_size = strtoul(buffer_arr_size, NULL, 10);
        return SUCCESS;
    }
}

int get_int(FILE* ptr) {
    assert(ptr != 0);
    char buffer_int[MAX_INT_LENGTH];
    int flag_input = fscanf(ptr, "%s", buffer_int);
    assert(flag_input != -1);
    return (int)strtol(buffer_int, NULL, 10);
}

From_file* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    assert(file != NULL);

    size_t arr_size = 0;
    int error_flag = get_arr_size(file, &arr_size);
    assert(error_flag != FAILURE || arr_size != 0);

    From_file* result_arr = (From_file*)malloc(sizeof(From_file));
    if (result_arr == NULL) {
        fclose(file);
        return NULL;
    }
    result_arr->arr_size = arr_size;
    result_arr->temperature_array = (int*)calloc(result_arr->arr_size, sizeof(int));
    if (result_arr->temperature_array == NULL) {
        free(result_arr);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < result_arr->arr_size; ++i) {
        result_arr->temperature_array[i] = get_int(file);
    }
    fclose(file);
    return result_arr;
}

int free_arr_from_file(From_file* ptr) {
    if (ptr == NULL) {
        return FAILURE;
    }
    free(ptr->temperature_array);
    free(ptr);
    return SUCCESS;
}