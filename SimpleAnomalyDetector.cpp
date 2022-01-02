// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490

#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(void) {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector(void) {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    lifeTime = ts.GetTimeOfLife();
    vector<string> paramNames = ts.GetParameterNames();
    int numOfParams = paramNames.size();
    //iterate through the feature couples:
    for (int i = 0; i < numOfParams; ++i) {
        vector<float> pivotVals = ts.GetParameterVals(paramNames[i]);
        FindCorrelatiosOfParam(pivotVals, i, ts);
    }
}

bool SimpleAnomalyDetector::areCorrelated(vector<float> &pivotVals, vector<float> &maxVals, float maxPear) {
    float pearsonThresh = pearThresh;
    float pear = fabs(pearson(pivotVals.data(), maxVals.data(), pivotVals.size()));
    //add if corelated:
    if ((pear >= pearsonThresh) && (pear > maxPear)) {
        return true;
    }
    return false;
}

void SimpleAnomalyDetector::FindCorrelatiosOfParam(vector<float>& pivotVals, int pivotIndex, const TimeSeries& ts)
{
    float maxPear = -1;
    int maxIndex = -1;
    std::vector<float> maxVals;

    vector<string> paramNames = ts.GetParameterNames();
    //find the param that is most correlated to the pivot
    for (int j = pivotIndex + 1; j < ts.GetNumOfParameters(); ++j) {
        maxVals = ts.GetParameterVals(paramNames[j]);
        float pear = fabs(pearson(pivotVals.data(), maxVals.data(), pivotVals.size()));
        //add if corelated:
        if (areCorrelated(pivotVals, maxVals, maxPear)) {
            maxIndex = j;
            maxPear = pear;
        }
    }
    if (maxIndex < 0)
        return;

    maxVals = ts.GetParameterVals((ts.GetParameterNames()[maxIndex]));

    //now we know that pivotIndex and maxIndex are correlated
    correlatedFeatures corr;
    corr.feature1 = paramNames[pivotIndex];
    corr.feature2 = paramNames[maxIndex];
    corr.corrlation = maxPear;

    vector<Point> points;
    for (int i = 0; i < pivotVals.size(); ++i)
    {
        points.push_back(Point(pivotVals[i], maxVals[i]));
    }
    auto tmp = points.data();
    findThresh(points.data(), points.size(), corr);
    m_cf.push_back(corr);
}

float SimpleAnomalyDetector::findThresh(Point* points, int size, correlatedFeatures& corr) {
    corr.lin_reg = linear_reg(&points, size);
    float maxDev = 0;
    //check for max dev:
    for (int k = 0; k < size; ++k) {
        float d = dev(points[k], corr.lin_reg);
        if(d > maxDev)
            maxDev = d;
    }
    corr.threshold = maxDev * 1.1;
    return maxDev * 1.1;
}

bool SimpleAnomalyDetector::isAnomaly(correlatedFeatures &corr, float x, float y) {
    bool result = (dev(Point(x, y), corr.lin_reg) > corr.threshold);
    return result;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    lifeTime = ts.GetTimeOfLife();
    unsigned int end = ts.GetTimeOfLife();
    for (auto it = m_cf.begin(); it != m_cf.end(); ++it) {
        for (int i = 0; i < end; i++) {
            float x = ts.GetValuesOfFeatureAtTime(i, it->feature1);
            float y = ts.GetValuesOfFeatureAtTime(i, it->feature2);

            if(isAnomaly(it.operator*(), x, y)){
                AnomalyReport report(it->feature1 + "-" + it->feature2,i+1);
                reports.push_back(report);
            }
        }

    }
    return reports;
}
