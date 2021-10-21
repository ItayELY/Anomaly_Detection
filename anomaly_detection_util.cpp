//
// Created by itaye on 19/10/2021.
//
#include <stdio.h>
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

// returns average of floats
float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

/*
int main() {
    float nums[] = {10, 20, 30, 40};
    float nums2[] = {55, 76, 27, 35};
    float variance = var(nums, 4);
    float covariance = cov(nums, nums2, 4);
    printf("%f", variance);
    printf("%f", covariance);
}
*/

// returns the variance of X and Y
float var(float *x, int size) {
    float average = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(abs(x[i] - average), 2.0);
    }
    return sum / size;
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum = sum + (x[i] - avg(x, size)) *
                    (y[i] - avg(x, size));

    return sum / (size - 1);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    float covariance = cov(x, y, size);
    float variance_x = var(x, size);
    float variance_y = var(y, size);
    float deviation_x = sqrt(variance_x);
    float deviation_y = sqrt(variance_y);
    return (covariance / (deviation_x * deviation_y));
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size){
    float *x = new float(size), *y = new float(size);
    float xAvg, yAvg, a, b;

    for (int i = 0; i < size; ++i) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }

    xAvg = avg(x, size);
    yAvg = avg(y, size);

    a = cov(x, y, size) / var(x, size);
    b = yAvg - (a * xAvg);

    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float yPointOnAxis = l.f(p.x);
    return abs(p.y - yPointOnAxis);
}


