#include "matrix.h"


int main(void) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test6.txt");
    assert(mat != NULL && mat->rows != 0 && mat->columns);
    
    print_mat(mat);
    
    double res = get_most_popular_elem(mat, mat->rows, mat->columns);
    printf("The most popular element int matrix is: %lf\n", res);

    free_matrix(mat);
    return 0;
}
