// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490
#include <stdio.h>
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

// returns average of floats
float avg(float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}


// returns the variance of X and Y
float var(float* x, int size) {
    float average = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(x[i] - average, 2.0);
    }
    return sum / size;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float result = 0;
    std::vector<float> multi;
    for (int i = 0; i < size; i++) {
        multi.push_back(x[i] * y[i]);
    }
    result = (avg(multi.data(), size) - avg(x, size) * avg(y, size));
    return (result);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float covariance = cov(x, y, size);
    float variance_x = var(x, size);
    float variance_y = var(y, size);
    float deviation_x = sqrt(variance_x);
    float deviation_y = sqrt(variance_y);
    return (covariance / (deviation_x * deviation_y));
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    std::vector<float> x(size), y(size);
    float xAvg, yAvg, a, b;

    for (int i = 0; i < size; ++i) {
        x[i] = (*points)[i].x;
        y[i] = (*points)[i].y;
    }

    xAvg = avg(x.data(), size);
    yAvg = avg(y.data(), size);

    a = cov(x.data(), y.data(), size) / var(x.data(), size);
    b = yAvg - (a * xAvg);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    float yPointOnAxis = l.f(p.x);
    return fabs(p.y - yPointOnAxis);
}



