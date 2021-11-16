
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(void) {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector(void) {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    vector<string> paramNames = ts.GetParameterNames();
    int numOfParams = paramNames.size();
    //iterate through the feature couples:
    for (int i = 0; i < numOfParams; ++i) {
        vector<float> pivotVals = ts.GetParameterVals(paramNames[i]);
        FindCorrelatiosOfParam(pivotVals, i, ts);
    }
}

void SimpleAnomalyDetector::FindCorrelatiosOfParam(vector<float>& pivotVals, int pivotIndex, const TimeSeries& ts)
{
    float maxPear = -1;
    int maxIndex = -1;
    std::vector<float> maxVals;

    vector<string> paramNames = ts.GetParameterNames();
    float pearsonThresh = 0.9;
    //find the param that is most correlated to the pivot
    for (int j = pivotIndex + 1; j < ts.GetNumOfParameters(); ++j) {
        maxVals = ts.GetParameterVals(paramNames[j]);
        float pear = fabs(pearson(pivotVals.data(), maxVals.data(), pivotVals.size()));
        //add if corelated:
        if ((pear >= pearsonThresh) && (pear > maxPear)) {
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
    corr.lin_reg = linear_reg(&tmp, points.size());

    float maxDev = 0;
    //check for max dev:
    for (int k = 0; k < pivotVals.size(); ++k) {
        float d = dev(points[k], corr.lin_reg);
        if(d > maxDev)
            maxDev = d;
    }
    corr.threshold = maxDev * 1.1;
    m_cf.push_back(corr);
}

//vector<Point> SimpleAnomalyDetector::createAllPoints(const TimeSeries& ts, unsigned int zeroBasedTime){
//    vector<Point> points;
//    for (auto it = m_cf.begin(); it != m_cf.end(); ++it) {
//        float x = ts.GetValuesOfFeatureAtTime(zeroBasedTime, it->feature1);
//        float y = ts.GetValuesOfFeatureAtTime(zeroBasedTime, it->feature2);
//        points.push_back(Point(x, y));
//    }
//    return points
//}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    vector<AnomalyReport> reports;
    unsigned int end = ts.GetTimeOfLife();
    for (auto it = m_cf.begin(); it != m_cf.end(); ++it) {
        for (int i = 0; i < end; i++) {
            float x = ts.GetValuesOfFeatureAtTime(i, it->feature1);
            float y = ts.GetValuesOfFeatureAtTime(i, it->feature2);
            if(dev(Point(x, y), it->lin_reg) > it->threshold){
                AnomalyReport report(it->feature1 + "-" + it->feature2,i+1);
                reports.push_back(report);
            }
        }
    }
    return reports;
}
