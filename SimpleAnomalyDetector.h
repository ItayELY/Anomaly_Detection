// Created By Itay Elyashev, id:212356364
// And Yonadav Leibowitz, id:207424490

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
    float threshold;
    Point middle;
	float radius;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> m_cf;
	float pearThresh = 0.9;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

    float getPearThresh(){return pearThresh;};
    void setPearThresh(float pearThresh){this->pearThresh = pearThresh;}
	void learnNormal(const TimeSeries& ts);
    void FindCorrelatiosOfParam(vector<float>& pivotVals, int pivotIndex, const TimeSeries& ts);
    vector<Point> createAllPoints(const TimeSeries& ts, unsigned int zeroBasedTime);

    virtual bool areCorrelated(vector<float>& pivotVals, vector<float>& maxVals, float maxPear);
    virtual float findThresh(Point* points, int size, correlatedFeatures& corr);

    virtual bool isAnomaly(correlatedFeatures& corr, float x, float y);
    vector<AnomalyReport> detect(const TimeSeries& ts);


	vector<correlatedFeatures> getNormalModel(){
		return m_cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
