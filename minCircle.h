//
// Created by itaye on 09/12/2021.
//


#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);
Circle circleFrom3Points(Point* p1, Point* p2, Point* p3);
Circle minCircleFrom2Points(Point* p1, Point* p2);
bool arePointsInCircle(Point** points, size_t size, Circle c);
float pointsDistance(Point* p1, Point* p2);
bool isInCircle(Point* p, Circle c);
int orientationOf3Points(Point* p1, Point* p2, Point* p3);
vector<Point*> findConvexHall(Point** points, size_t size);

#endif /* MINCIRCLE_H_ */
