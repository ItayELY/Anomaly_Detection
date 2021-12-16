// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490

#ifndef ANOMALY_DETECTION_HYBRIDANOMALYDETECTOR_H
#define ANOMALY_DETECTION_HYBRIDANOMALYDETECTOR_H

#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>


class HybridAnomalyDetector:public SimpleAnomalyDetector{
    virtual bool areCorrelated(vector<float>& pivotVals, vector<float>& maxVals, float maxPear);
    virtual float findThresh(Point* points, int size, correlatedFeatures& corr);
    virtual bool isAnomaly(correlatedFeatures& corr, float x, float y);
};

#endif //ANOMALY_DETECTION_HYBRIDANOMALYDETECTOR_H
