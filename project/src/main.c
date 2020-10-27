#include "utils.h"
#include "ST/ST_temperature_jump.h"
#include "MT/MT_temperature_jump.h"




int main() {
    From_file* arr = read_file(SOURCE_DIR"/project/tests/data/test.txt");
    assert(arr != NULL);

    int n_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);

    struct timespec start, finish;

    if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &start) == -1) {
        return EXIT_FAILURE;
    };
    int res_ST = ST_calculate_temperature_jump(arr->temperature_array, arr->arr_size);
    if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &finish) == -1) {
        return EXIT_FAILURE;
    };
    double time_ST = (double)(finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000;


    if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &start) == -1) {
        return EXIT_FAILURE;
    };

    int res_MT = MT_calculate_temperature_jump(arr->temperature_array, arr->arr_size, n_threads);

    if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &finish) == -1) {
        return EXIT_FAILURE;
    };
    double time_MT = (double)(finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000;



    printf("Результат вычислений однопоточного алгоритма: %d\n", res_ST);
    printf("Время работы однопоточного алгоритма: %f", time_ST);
    printf("\n");
    printf("Результат вычислений многопоточного алгоритма: %d\n", res_MT);
    printf("Время работы многопоточного алгоритма: %f", time_MT);


    free_arr_from_file(arr);
    return 0;
}
