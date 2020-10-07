#include "matrix.h"


// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* ptr = fopen(path_file, "r");
    if (ptr == NULL) {
        return NULL;
    } else {
        size_t rows_n, cols_n;
        fscanf(ptr, "%zu %zu", &rows_n, &cols_n);
        Matrix* temp = create_matrix(rows_n, cols_n);
        if (temp == NULL) {
            fclose(ptr);
            return NULL;
        }
        for (size_t i = 0; i < temp->rows; i++) {
            for (size_t j = 0; j < temp->columns; j++) {
                fscanf(ptr, "%lf", &temp->elements[i][j]);
            }
        }
        fclose(ptr);
        return temp;
    }
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->columns = cols;
    matrix->elements = (double**)malloc(sizeof(double*) * rows);
    if (matrix->elements == NULL) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->elements[i] = (double*)malloc(sizeof(double) * cols);
        if (matrix->elements[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix->elements[j]);
            }
            free(matrix->elements);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}


void print_mat(const Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }
    printf("rows: %zu\ncols: %zu\n", matrix->rows, matrix->columns);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->columns; j++) {
            printf("%lf ", matrix->elements[i][j]);
        }
        printf("\n");
    }
}



int free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return 1;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix);
    return 0;
}

// Basic operations
/*
int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL || rows == NULL) {
        return 1;
    }
    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL || cols == NULL) {
        return 1;
    }
    *cols = matrix->columns;
    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL || val == NULL) {
        return 1;
    }
    *val = matrix->elements[row][col];
    return 0;
}
*/

double* get_one_dim_arr(const Matrix* matrix, size_t size) {
    double* one_dim_arr = (double*)malloc(sizeof(double) * size);
    if (one_dim_arr == NULL) {
        return NULL;
    }
    size_t position = 0;
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->columns; ++j) {
            one_dim_arr[position] = matrix->elements[i][j];
            position += 1;
        }
    }
    return one_dim_arr;
}

int get_most_popular_elem(const Matrix* matrix, double* most_popular_elem) {
    if (matrix == NULL) {
        return 1;
    }
    size_t size_one_dim_arr = matrix->rows * matrix->columns;
    double* one_dim_arr = get_one_dim_arr(matrix, size_one_dim_arr);
    if (one_dim_arr == NULL) {
        return 1;
    }

    size_t index_most_popular_elem = 0;
    int max_count = 1;

    for (size_t i = 0; i < size_one_dim_arr; ++i) {
        int count = 1;
        for (size_t j = i + 1; j < size_one_dim_arr; j++) {
            if (one_dim_arr[i] == one_dim_arr[j]) {
                count += 1;
            }
        }
        if (count > max_count) {
	         index_most_popular_elem = i;
             max_count = count;
        }
    }

    *most_popular_elem = one_dim_arr[index_most_popular_elem];
    free(one_dim_arr);
    return 0;
}

