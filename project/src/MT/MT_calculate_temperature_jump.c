//
// Created by steve on 26.10.2020.
//
#include "MT/MT_temperature_jump.h"


// дефолтная инициализация глобальной переменной
data_t data = {PTHREAD_MUTEX_INITIALIZER, 0, 0};

// потоковая функция
void* calculate_max_jump(void *arg) {
    for_thread_routine* args = (for_thread_routine*)arg;

    assert(args->arr != NULL && args->begin >= 0 && args->end < args->size);

    for(int i = args->begin + 1; i <= args->end; ++i) {
        if(args->arr[i] > args->arr[i - 1]) {
            int current_jump = args->arr[i] - args->arr[i - 1];
            if(current_jump > args->max_jump) {
                args->max_jump = current_jump;
                args->time_index = i - 1;
            }
        }
    }

    pthread_mutex_t* mutex = &data.mutex;
    int error_flag = pthread_mutex_lock(mutex);
    // проверяем успешное завершение pthread_mutex_lock
    assert(error_flag == 0);

    if (args->max_jump > data.max_jump) {
        data.max_jump = args->max_jump;
        data.time_index = args->time_index;
    }

    error_flag = pthread_mutex_unlock(mutex);
    // проверяем успешное завершение pthread_mutex_unlock
    assert(error_flag == 0);
    return arg;
}

// функция для разбиения исходного массива на части для потоков
int* partition(int size_arr, int n_threads, int amount_indexes) {
    assert(size_arr >= amount_indexes);

    int* result_indexes = (int*)calloc(amount_indexes, sizeof(int));
    assert(result_indexes != NULL);

    int step = (size_arr / n_threads) - 1;
    int index = 1;
    for(int i = step; i < size_arr - 2; i += step) {
        result_indexes[index] = i;
        index += 1;
        result_indexes[index] = i + 1;
        index += 1;
        i += 1;
    }
    result_indexes[amount_indexes - 1] = size_arr - 1;
    return result_indexes;
}

// функция для обработки стыков разбиения исходного массива
void check_joints(const int* arr, int size_arr, const int* indexes, int amount_indexes) {
    assert(size_arr >= amount_indexes);
    for (int i = 1; i < amount_indexes - 2; ++i) {
        if (arr[indexes[i]] < arr[indexes[i + 1]]) {
            int current_jump = arr[indexes[i + 1]] - arr[indexes[i]];
            if(current_jump > data.max_jump) {
                data.max_jump = current_jump;
                data.time_index = indexes[i];
            }
        }
    }
}

int MT_calculate_temperature_jump(const int* arr, int size, int n_threads) {
    // получаем индексы для разбиения массива на части
    int amount_indexes = n_threads * 2;
    int* indexes = partition(size, n_threads, amount_indexes);
    assert(indexes != NULL);

    // инициализируем глобальные переменные дефорлтными значениями
    data.max_jump = 0;
    data.time_index = NOT_FOUND;

    // запускае n потоков в цикле и проверяем на ошибки
    pthread_t thread_id[n_threads];
    for_thread_routine args[n_threads];
    int error_flag[n_threads];

    pthread_mutex_init(&data.mutex, NULL);

    for (int i = 0; i < n_threads; i++) {
        args[i].arr = arr;
        args[i].size = size;
        args[i].begin = indexes[i * 2];
        args[i].end = indexes[i * 2 + 1];
        args[i].max_jump = 0;
        args[i].time_index = NOT_FOUND;

        error_flag[i] = 0;

        error_flag[i] = pthread_create(&thread_id[i],
                                    NULL,
                                    calculate_max_jump,
                                    (void*) &args[i]);
        assert(error_flag[i] == 0);
    }

    // ждем завершения потоков
    for (int i = 0; i < n_threads; i++) {
        error_flag[i] = pthread_join(thread_id[i], NULL);
        assert(error_flag[i] == 0);
    }

    pthread_mutex_destroy(&data.mutex);

    // проверяем значения скачков на стыке разбиения
    check_joints(arr, size, indexes, amount_indexes);
    free(indexes);
    // возвращаем время максимального скачка
    return data.time_index;
}