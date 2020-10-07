#ifndef _HOME_STEVE_TP_MAIL_CPP_TP_IZ1_PROJECT_INCLUDE_MATRIX_H_
#define _HOME_STEVE_TP_MAIL_CPP_TP_IZ1_PROJECT_INCLUDE_MATRIX_H_
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

// Basic operations
// int get_rows(const Matrix* matrix, size_t* rows);
// int get_cols(const Matrix* matrix, size_t* cols);
// int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);


#endif  // _HOME_STEVE_TP_MAIL_CPP_TP_IZ1_PROJECT_INCLUDE_MATRIX_H_
