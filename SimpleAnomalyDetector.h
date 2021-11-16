

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> m_cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
    void FindCorrelatiosOfParam(vector<float>& pivotVals, int pivotIndex, const TimeSeries& ts);
    vector<Point> createAllPoints(const TimeSeries& ts, unsigned int zeroBasedTime);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	vector<correlatedFeatures> getNormalModel(){
		return m_cf;
	}

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
