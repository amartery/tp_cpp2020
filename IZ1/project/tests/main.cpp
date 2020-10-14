#include <gtest/gtest.h>


extern "C" {
    #include "matrix.h"
}

// стандартый тест (стандартное поведение)
TEST(get_most_popular_elem, test1) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test1.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, -5.940000);
}

// тест: один элемент в матрице (возвращается этот элемент)
TEST(get_most_popular_elem, test2) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test2.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, 345.000000);
}

// тест: все элементы в матрице разные (возвращается первый элемент матрицы)
TEST(get_most_popular_elem, test3) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test3.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, 1.000000);
}

// тест: все элементы матрицы повторяются одинаковое количество раз (возвращается первый элемент)
TEST(get_most_popular_elem, test4) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test4.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, 1.000000);
}

// тест: все элементы матрицы одинаковые (возвращается первый элемент)
TEST(get_most_popular_elem, test5) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test5.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, 1.000000);
}

// тест: не полностью инициализированная матрица (пропущенные элементы инициализируются нулями)
TEST(get_most_popular_elem, test6) {
    Matrix *mat = create_matrix_from_file(SOURCE_DIR"/tests/data/test6.txt");
    if (mat == NULL) {
        printf("couldn't open the file\n");
    }
    print_mat(mat);
    double result = get_most_popular_elem(mat);
    free_matrix(mat);

    ASSERT_EQ(result, 0.000000);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


