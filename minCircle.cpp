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

        return Circle(*center, pointsDistance(center, p1));

}

double pointsDistance(Point *p1, Point *p2){
    double distance = sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
    return distance;
}

bool isInCircle(Point* p, Circle* c){
    return (pointsDistance(p, &(c->center)) <= c->radius);
}
/*
Circle findMinCircle(Point** points,size_t size){

}
 */