#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_
#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix {
    size_t rows;
    size_t columns;
    double** elements;
} Matrix;

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

void print_mat(const Matrix* matrix);
int get_most_popular_elem(const Matrix* matrix, double* most_popular_elem);

#endif  // PROJECT_INCLUDE_MATRIX_H_
