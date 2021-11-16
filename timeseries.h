

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class TimeSeries{

    struct Param
    {
        string name;
        vector<float> vals;
    };

private:
    vector<Param> m_table;

public:
	TimeSeries(const char* CSVfileName);
    vector<float> GetParameterVals(const string& param) const;
    vector<float> GetValuesAtTime(unsigned int oneBasedTime);
    float GetValuesOfFeatureAtTime(unsigned int oneBasedTime, const string& param) const;
    vector<string> GetParameterNames() const;
    unsigned int GetNumOfParameters() const;
    unsigned int GetTimeOfLife() const;
    void PrintTable();
};



#endif /* TIMESERIES_H_ */
