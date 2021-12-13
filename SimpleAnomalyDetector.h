

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
	bool isLinear;
	float corrlation;
	Line lin_reg;
	Point middle;
	float radius;
	float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> m_cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

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
