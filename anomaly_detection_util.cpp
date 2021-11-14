// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490
#include <stdio.h>
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>

// returns average of floats
float avg(std::vector<float> x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}


// returns the variance of X and Y
float var(std::vector<float> x, int size) {
    x.resize(size);
    float average = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow(x[i] - average, 2.0);
    }
    return sum / size;
}

// returns the covariance of X and Y
float cov(std::vector<float> x, std::vector<float> y, int size) {
    x.resize(size);
    y.resize(size);

    float result = 0;
    std::vector<float> multi;
    for (int i = 0; i < size; i++) {
        multi.push_back(x[i] * y[i]);
    }
    result = (avg(multi, size) - avg(x, size) * avg(y, size));
    return (result);
}

// returns the Pearson correlation coefficient of X and Y
float pearson(std::vector<float> x, std::vector<float> y, int size) {
    x.resize(size);
    y.resize(size);

    float covariance = cov(x, y, size);
    float variance_x = var(x, size);
    float variance_y = var(y, size);
    float deviation_x = sqrt(variance_x);
    float deviation_y = sqrt(variance_y);
    return (covariance / (deviation_x * deviation_y));
}

// performs a linear regression and return s the line equation
Line linear_reg(std::vector<Point> points, int size) {
    points.resize(size);

    std::vector<float> x, y;
    float xAvg, yAvg, a, b;

    for (int i = 0; i < size; ++i) {
        x[i] = points[i].x;
        y[i] = points[i].y;
    }

    xAvg = avg(x, size);
    yAvg = avg(y, size);

    a = cov(x, y, size) / var(x, size);
    b = yAvg - (a * xAvg);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, std::vector<Point> points, int size) {
    points.resize(size);

    Line line = linear_reg(points, size);
    return dev(p, line);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    float yPointOnAxis = l.f(p.x);
    return fabs(p.y - yPointOnAxis);
}



