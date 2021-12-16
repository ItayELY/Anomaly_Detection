// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490
#include "minCircle.h"
#include <math.h>
#define INFINITY 9999999999
Circle circleFrom3Points(Point* p1, Point* p2, Point* p3){
        float bx = p2->x - p1->x, by = p2->y - p1->y
                , cx = p3->x - p1->x, cy = p3->y - p1->y;
        float B = bx * bx + by * by;
        float C = cx * cx + cy * cy;
        float D = bx * cy - by * cx;

        Point* center = new Point(((cy * B - by * C) / (2 * D)) + p1->x,
                                            ((bx * C - cx * B) / (2 * D)) + p1->y);

        return {*center, pointsDistance(*center, *p1)};

}

Circle minCircleFrom2Points(Point* p1, Point* p2){
    Point cen((p1->x + p2->x) / 2.0, (p1->y + p2->y) / 2.0);
    return Circle(cen, (pointsDistance(*p1, *p2) / 2));
}

bool arePointsInCircle(Point* points, size_t size, Circle c){
    for (int i = 0; i < size; ++i) {
        if (!isInCircle(points[i], c)){
            return false;
        }
    }
    return true;
}

float pointsDistance(Point p1, Point p2){
    return sqrtf(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

bool isInCircle(Point p, Circle c){
    return (pointsDistance(p, (c.center)) <= c.radius);
}

int orientationOf3Points(Point* p1, Point* p2, Point* p3){
    int ori = ((p2->y - p1->y) * (p3->x - p2->x)) - ((p2->x - p1->x) * (p3->y - p2->y));
    if (ori > 0){
        return 1;
    }
    if (ori < 0){
        return 2;
    }
    return ori;
}

vector<Point*> findConvexHall(Point* points, size_t size){
    vector<Point*> result(0);
    if (size < 3){
        for (int i = 0; i < size; ++i) {
            result.push_back(&points[i]);
        }
        return result;
    }

    int leftMostIndx = 0;
    //find leftmost index:
    for (int i = 1; i < size; ++i) {
        if (points[i].x < points[leftMostIndx].x){
            leftMostIndx = i;
        }
    }
    int p1 = leftMostIndx, p2;
    //go counter-clockwise and add the relevant points to result
    do{
        //add current point
        result.push_back(&points[p1]);
        //find the most counter-clockwise point to p1
        p2 = (p1 + 1)%size;
        for (int i = 0; i < size; ++i) {
            //if new point more counter-clockwise then update
            if (orientationOf3Points(&points[p1], &points[p2], &points[i]) == 2){
                p2 = i;
            }
        }
        //new relevant point
        p1 = p2;
    }while (p1 != leftMostIndx);//while we don't return to the start

    return  result;
}


Circle findMinCircle(Point** points,size_t size){
    Circle minCircle(Point(0, 0), INFINITY);

    vector<Point*> betterPoints = findConvexHall(*points, size);
    //find minimum between each 2 points
    for (int i = 0; i < betterPoints.size(); ++i) {
        for (int j = 0; j < betterPoints.size(); ++j) {
            Circle cir = minCircleFrom2Points(betterPoints[i], betterPoints[j]);
            if (arePointsInCircle(*points, size, cir)){
                if (cir.radius < minCircle.radius){
                    minCircle = cir;
                }
            }
        }

    }
    //find minimum between each 3 points
    for (int i = 0; i < betterPoints.size(); ++i) {
        for (int j = i; j < betterPoints.size(); ++j) {
            for (int k = j; k < betterPoints.size(); ++k) {
                Circle cir = circleFrom3Points(betterPoints[i], betterPoints[j], betterPoints[k]);
                if (arePointsInCircle(*points, size, cir)){
                    if (cir.radius < minCircle.radius){
                        minCircle = cir;
                    }
                }
            }
        }
    }
    return minCircle;
}