//
// Created by steve on 22.10.2020.
//
#include <gtest/gtest.h>
#include <iostream>
#include <chrono>

extern "C" {
#include "utils.h"
#include "ST/ST_temperature_jump.h"
#include "MT/MT_temperature_jump.h"
}

// стандартый тест (стандартное поведение)
TEST(ST_calculate_temperature_jump, test1) {
    int arr[] = {-1, 0, -1, 2, 6};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, 3);
}

// тест: температура убывает
TEST(ST_calculate_temperature_jump, test2) {
    int arr[] = {1, 0, -1, -2, -3};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, -1);
}

// тест: температура не меняется
TEST(ST_calculate_temperature_jump, test3) {
    int arr[] = {1, 1, 1, 1, 1};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, -1);
}

// тест: один положительный скачок
TEST(ST_calculate_temperature_jump, test4) {
    int arr[] = {1, 1, 1, -5, 1};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, 3);
}

// тест: нет положительных скачков
TEST(ST_calculate_temperature_jump, test5) {
    int arr[] = {1, 1, 1, -5, -5};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, -1);
}

// стандартый тест (стандартное поведение) (многопоточный)
TEST(MT_calculate_temperature_jump, test6) {
    int arr[] = {-1, 0, -1, 2, 6};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 2;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, 3);
}

// тест: температура убывает (многопоточный)
TEST(MT_calculate_temperature_jump, test7) {
    int arr[] = {1, 0, -1, -2, -3};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 2;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, -1);
}

// тест: температура не меняется (многопоточный)
TEST(MT_calculate_temperature_jump, test8) {
    int arr[] = {1, 1, 1, 1, 1};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 2;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, -1);
}

// тест: один положительный скачок (многопоточный)
TEST(MT_calculate_temperature_jump, test9) {
    int arr[] = {1, 1, 1, -5, 1};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 2;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, 3);
}

// тест: нет положительных скачков (многопоточный)
TEST(MT_calculate_temperature_jump, test10) {
    int arr[] = {1, 1, 1, -5, -5};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 2;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, -1);
}

// тест: максимальный скачок на стыке разбиения (многопоточный)
TEST(MT_calculate_temperature_jump, test11) {
    int arr[] = {0, 1, 7, 6, 5, 4, 6, 6};
    int size_arr = sizeof(arr) / sizeof(int);
    int n_threads = 4;
    int result = MT_calculate_temperature_jump(arr, size_arr, n_threads);
    ASSERT_EQ(result, 1);
}

// тест: максимальный скачок на стыке разбиения
TEST(MT_calculate_temperature_jump, test12) {
    int arr[] = {0, 1, 7, 6, 5, 4, 6, 6};
    int size_arr = sizeof(arr) / sizeof(int);
    int result = ST_calculate_temperature_jump(arr, size_arr);
    ASSERT_EQ(result, 1);
}

// тест: сравнение результатов и замер времени
TEST(comparison_MT_ST, test13) {
    From_file* arr = read_file(SOURCE_DIR"/project/tests/data/test.txt");
    assert(arr != nullptr);

    auto start = std::chrono::system_clock::now();
    int res_ST = ST_calculate_temperature_jump(arr->temperature_array, arr->arr_size);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_ST = end - start;

    int n_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);
    start = std::chrono::system_clock::now();
    int res_MT = MT_calculate_temperature_jump(arr->temperature_array,
                                               arr->arr_size,
                                               n_threads);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff_MT = end - start;

    sleep(1);

    std::cout << "Результаты:" << std::endl;
    std::cout << "Время работы однопоточного алгоритма: " << diff_ST.count() << std::endl;
    std::cout << "Время работы многопоточного алгоритма: " << diff_MT.count() << std::endl;
    std::cout << "res_ST: " << res_ST << " " << "res_MT: " << res_MT << std::endl;
    ASSERT_EQ(res_ST, res_MT);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

