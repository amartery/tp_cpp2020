#include "utils.h"
#include "ST/ST_temperature_jump.h"
#include "MT/MT_temperature_jump.h"




int main() {
    From_file* arr = read_file(SOURCE_DIR"/project/tests/data/test.txt");
    assert(arr != NULL);

    int n_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);

//    struct timeval start_ST;
//    gettimeofday(&start_ST, NULL);
//    int res_ST = ST_calculate_temperature_jump(arr->temperature_array, arr->arr_size);
//    struct timeval end_ST;
//    gettimeofday(&end_ST, NULL);
//    double time_ST = (end_ST.tv_sec - start_ST.tv_sec) * 1000 + (end_ST.tv_usec - start_ST.tv_usec) / 1000;
//
//    struct timeval start_MT;
//    gettimeofday(&start_MT, NULL);
//    int res_MT = MT_calculate_temperature_jump(arr->temperature_array, arr->arr_size, n_threads);
//    struct timeval end_MT;
//    gettimeofday(&end_MT, NULL);
//    double time_MT = (end_MT.tv_sec - start_MT.tv_sec) * 1000 + (end_MT.tv_usec - start_MT.tv_usec) / 1000;
//



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

    int res_MT = MT_calculate_temperature_jump(arr->temperature_array, arr->arr_size, 2);

    if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &finish) == -1) {
        return EXIT_FAILURE;
    };
    double time_MT = (double)(finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000;



    printf("Результат вычислений однопоточного алгоритма: %d\n", res_ST);
    printf("Время работы однопоточного алгоритма: %f", time_ST);
    printf("\n");
    printf("Результат вычислений многопоточного алгоритма: %d\n", res_MT);
    printf("Время работы многопоточного алгоритма: %f", time_MT);


    free(arr);
    return 0;
}
