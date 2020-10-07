#include "matrix.h"


int main(void) {
    Matrix *mat = create_matrix_from_file("/home/steve/tp_mail/cpp_tp/iz1/project/src/test1.txt");
    if (mat == NULL) {
        return 1;
    }
    print_mat(mat);

    double a = 0;
    get_most_popular_elem(mat, &a);
    printf("%lf\n", a);

    free_matrix(mat);
    return 0;
}


