//
// Created by itaye on 09/12/2021.
//
#include "minCircle.h"

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