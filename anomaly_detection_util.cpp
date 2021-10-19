//
// Created by itaye on 19/10/2021.
//
#include <stdio.h>
#include <iostream>
#include "anomaly_detection_util.h"

// returns average of floats
float avg(float* x, int size){
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

int main() {
    float nums[] = {10, 20, 30, 40};
    float varience = var(nums, 4);

    printf("%f", varience);
    return 1;
}



// returns the variance of X and Y
float var(float* x, int size){
    float average = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(abs(x[i] - average), 2.0);
    }
    return sum / size;
}

