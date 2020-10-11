#include "matrix.h"
#define MAX_DOUBLE_LENGTH 19
#define MAX_SIZE_T_LENGTH 5


int get_rows_n_cols_n(FILE* ptr, size_t* rows_n, size_t* cols_n) {
    if (ptr == NULL) {
        return 1;
    }
    char buffer_rows_n[MAX_SIZE_T_LENGTH];
    char buffer_cols_n[MAX_SIZE_T_LENGTH];
    int flag_input = fscanf(ptr, "%4s %4s", buffer_rows_n, buffer_cols_n);
    if (flag_input == -1) {
        return 1;
    } else {
        *rows_n = strtoul(buffer_rows_n, NULL, 10);
        *cols_n = strtoul(buffer_cols_n, NULL, 10);
        return 0;
    }
}

int get_double(FILE* ptr, double* value) {
    if (ptr == NULL) {
        return 1;
    }
    char buffer_double[MAX_DOUBLE_LENGTH];
    int flag_input = fscanf(ptr, "%18s", buffer_double);
    if (flag_input == -1) {
         *value = 0;
    } else {
        *value = strtod(buffer_double, NULL);
    }
    return 0;
}

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file) {
    FILE* ptr = fopen(path_file, "r");
    if (ptr == NULL) {
        return NULL;
    } else {
        size_t rows_n = 0, cols_n = 0;
        int flag = get_rows_n_cols_n(ptr, &rows_n, &cols_n);
        if (flag == 1 || rows_n == 0 || cols_n == 0) {
            fclose(ptr);
            return NULL;
        }
        Matrix* temp = create_matrix(rows_n, cols_n);
        if (temp == NULL) {
            fclose(ptr);
            return NULL;
        }
        for (size_t i = 0; i < temp->rows; i++) {
            for (size_t j = 0; j < temp->columns; j++) {
                get_double(ptr, &temp->elements[i][j]);
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

