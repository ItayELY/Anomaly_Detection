//
// Created by itaye on 13/12/2021.
//

#include "HybridAnomalyDetector.h"

bool HybridAnomalyDetector::areCorrelated(vector<float> &pivotVals, vector<float> &maxVals, float maxPear) {
    float pearsonThresh = 0.5;
    float pear = fabs(pearson(pivotVals.data(), maxVals.data(), pivotVals.size()));
    //add if corelated:
    if ((pear >= pearsonThresh) && (pear > maxPear)) {
        return true;
    }
    return false;
}
float HybridAnomalyDetector::findThresh(Point *points, int size, correlatedFeatures &corr) {
    if (corr.corrlation >= 0.9){
        return SimpleAnomalyDetector::findThresh(points, size, corr);
    }
    Circle cir = findMinCircle(&points, size);
    corr.middle = cir.center;
    corr.radius = cir.radius;
    corr.threshold = cir.radius * 1.1;
    return cir.radius * 1.1;
}

bool HybridAnomalyDetector::isAnomaly(correlatedFeatures &corr, float x, float y) {
    if (corr.corrlation >= 0.9){
        return SimpleAnomalyDetector::isAnomaly(corr, x, y);
    }
    Point point(x, y);
    if (pointsDistance(&point, &corr.middle) > corr.radius){
        return true;
    }
    return false;
}