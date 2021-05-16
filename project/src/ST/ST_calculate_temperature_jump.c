//
// Created by steve on 26.10.2020.
//
#include "ST/ST_temperature_jump.h"


int ST_calculate_temperature_jump(const int* arr, int size) {
    assert(arr != NULL && size > 0 );
    int max_jump = 0;
    int time_index = NOT_FOUND;

    for(int i = 1; i < size; ++i) {
        if(arr[i] > arr[i - 1]) {
            int current_jump = arr[i] - arr[i - 1];
            if(current_jump > max_jump) {
                max_jump = current_jump;
                time_index = i - 1;
            }
        }
    }
    return time_index;
}
