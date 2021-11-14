
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector(void) {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector(void) {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    vector<string> paramNames = ts.TimeSeries::GetParameters();
    int numOfParams = paramNames.size();
    //iterate through the feature couples:
    for (int i = 0; i < numOfParams; ++i) {
        vector<float> vals1 = ts.TimeSeries::GetParameterVals(paramNames[i]);
        float m = 0.9, c = -1;
        for (int j = 0; j < numOfParams; ++j) {
            std::vector<float> vals2 = ts.TimeSeries::GetParameterVals(paramNames[j]);
            float pear =  pearson(vals1, vals2, vals1.size());
            pear = fabs(pear);
            //add if corelated:
            if (pear > m){
                m = pear;
                c = j;
                correlatedFeatures corf;
                corf.corrlation = pear;
                corf.feature1 = paramNames[i];
                corf.feature2 = paramNames[j];
                //get linear regression:
                vector<float> pointsOf1= ts.TimeSeries::GetParameterVals(paramNames[i]);
                vector<float> pointsOf2= ts.TimeSeries::GetParameterVals(paramNames[j]);
                vector<Point> points;
                //get points for the line:
                for (int k = 0; k < pointsOf1.size(); ++k) {
                    points.push_back(Point(pointsOf1[k], pointsOf2[k]));
                }
                corf.lin_reg = linear_reg(points, points.size());
                int maxDev = 0;
                //check for max threshold:
                for (int k = 0; k < pointsOf1.size(); ++k) {
                    if(dev(points[k], corf.lin_reg) > maxDev){
                        maxDev = dev(points[k], corf.lin_reg);
                    }
                }
                corf.threshold = maxDev;
                cf.push_back(corf);
            }
        }
    }
}
/*
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}
*/
