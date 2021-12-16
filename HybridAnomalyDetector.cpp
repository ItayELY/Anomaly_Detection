// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490

#include "HybridAnomalyDetector.h"

bool HybridAnomalyDetector::areCorrelated(vector<float> &pivotVals, vector<float> &maxVals, float maxPear) {
    float pearsonThresh = 0.5;
    float pear = fabs(pearson(pivotVals.data(), maxVals.data(), pivotVals.size()));
    //add if corelated:
    if ((pear > pearsonThresh) && (pear > maxPear)) {
        return true;
    }
    return false;
}
float HybridAnomalyDetector::findThresh(Point *points, int size, correlatedFeatures &corr) {
    if (corr.corrlation >= 0.9){
        return SimpleAnomalyDetector::findThresh(points, size, corr);
    }
    Point** pointPtr = &points;
    Circle cir = findMinCircle(pointPtr, size);
    corr.middle = cir.center;
    corr.radius = cir.radius;
    corr.threshold = cir.radius * 1.1;
    return corr.threshold;
}

bool HybridAnomalyDetector::isAnomaly(correlatedFeatures &corr, float x, float y) {
    if (corr.corrlation >= 0.9){
        return SimpleAnomalyDetector::isAnomaly(corr, x, y);
    }
    Point point(x, y);
    if (pointsDistance(point, corr.middle) > corr.radius * 1.1){
        return true;
    }
    return false;
}