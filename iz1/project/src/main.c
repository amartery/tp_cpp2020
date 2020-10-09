#include "matrix.h"


int main(void) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test1.txt");
    if (mat == NULL) {
        return 1;
    }
    print_mat(mat);

    double res = 0;
    get_most_popular_elem(mat, &res);
    printf("The most popular element int matrix is: %lf\n", res);

    free_matrix(mat);
    return 0;
}

