

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

class TimeSeries{
    vector<string> names;
    vector<vector<float>> values;
public:
	TimeSeries(const char* CSVfileName){
        // File pointer
        fstream fin;
        // Open an existing file
        fin.open(CSVfileName, ios::in);


	}

};



#endif /* TIMESERIES_H_ */
