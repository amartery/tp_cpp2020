#include "matrix.h"


int main(void) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test6.txt");
    if (mat == NULL) {
        return 1;
    }
    print_mat(mat);

    double res = get_most_popular_elem(mat);
    printf("The most popular element int matrix is: %lf\n", res);

    free_matrix(mat);
    return 0;
}
