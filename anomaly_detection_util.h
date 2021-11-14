//
// Created by itaye on 19/10/2021.
//
// returns the variance of X and Y
#include <vector>

float var(std::vector<float> x, int size);
// returns the covariance of X and Y
float cov(std::vector<float> x, float* y, int size);
// returns the Pearson correlation coefficient of X and Y
float pearson(std::vector<float> x, std::vector<float> y, int size);
class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x){
        return a*x+b;
    }
};
class Point{
public:
    float x,y;
    Point(float x, float y):x(x),y(y){}
};
// performs a linear regression and return s the line equation
Line linear_reg(std::vector<Point> points, int size);
// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size);
// returns the deviation between point p and the line
float dev(Point p,Line l);

#ifndef ANOMALY_DETECTION_ANOMALY_DETECTION_UTIL_H
#define ANOMALY_DETECTION_ANOMALY_DETECTION_UTIL_H

#endif //ANOMALY_DETECTION_ANOMALY_DETECTION_UTIL_H
