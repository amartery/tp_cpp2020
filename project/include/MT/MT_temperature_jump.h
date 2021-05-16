//
// Created by steve on 27.10.2020.
//
#ifndef IZ2_MT_TEMPERATURE_JUMP_H
#define IZ2_MT_TEMPERATURE_JUMP_H

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define NOT_FOUND -1

// критическая секция для потоков
typedef struct {
    pthread_mutex_t mutex;
    int max_jump;
    int time_index;
} data_t;

// данные для передачи в потокувую функцию
typedef struct {
    const int* arr;
    int size;
    int begin;
    int end;
    int max_jump;
    int time_index;
} for_thread_routine;

int MT_calculate_temperature_jump(const int* arr, int size, int n_threads);
#endif //IZ2_MT_TEMPERATURE_JUMP_H
