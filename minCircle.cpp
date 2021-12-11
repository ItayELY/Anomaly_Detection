//
// Created by itaye on 09/12/2021.
//
#include "minCircle.h"

Circle circleFrom3Points(Point* p1, Point* p2, Point* p3){
        float bx = p2->x - p1->x, by = p2->y - p1->y
                , cx = p3->x - p1->x, cy = p3->y - p1->y;
        float B = bx * bx + by * by;
        float C = cx * cx + cy * cy;
        float D = bx * cy - by * cx;

        Point* center = new Point(((cy * B - by * C) / (2 * D)) + p1->x,
                                            ((bx * C - cx * B) / (2 * D)) + p1->y);

        return {*center, pointsDistance(center, p1)};

}

Circle minCircleFrom2Points(Point* p1, Point* p2){
    Point cen((p1->x + p2->x) / 2.0, (p1->y + p2->y) / 2.0);
    return Circle(cen, (pointsDistance(p1, p2) / 2));
}

bool arePointsInCircle(Point** points, size_t size, Circle c){
    for (int i = 0; i < size; ++i) {
        if (!isInCircle(points[i], c)){
            return false;
        }
    }
    return true;
}

float pointsDistance(Point *p1, Point *p2){
    float distance = sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
    return distance;
}

bool isInCircle(Point* p, Circle c){
    return (pointsDistance(p, &(c.center)) <= c.radius);
}

Circle findMinCircle(Point** points,size_t size){
    Circle minCircle(Point(0, 0), INFINITY);

    //find minimum between each 2 points
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Circle cir = minCircleFrom2Points(points[i], points[j]);
            if (arePointsInCircle(points, size, cir)){
                if (cir.radius < minCircle.radius){
                    minCircle = cir;
                }
            }
        }

    }
    //find minimum between each 3 points
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                Circle cir = circleFrom3Points(points[i], points[j], points[k]);
                if (arePointsInCircle(points, size, cir)){
                    if (cir.radius < minCircle.radius){
                        minCircle = cir;
                    }
                }
            }
        }
    }
    return minCircle;
}