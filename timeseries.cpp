#include "timeseries.h"
#include <fstream>
#include <sstream>

TimeSeries::TimeSeries(const char *CSVfileName) {
    // File pointer
    ifstream fin;
    // Open an existing file
    fin.open(CSVfileName);
    bool ok = fin.is_open();

    string lineBuf;
    char delimiter = ',';
    string paramName;
    string paramVal;

    //read first line
    getline(fin, lineBuf);
    istringstream line(lineBuf);
    //loop over the param names in the first line
    while (std::getline(line, paramName, delimiter)) {
        Param p;
        p.name = paramName;
        //p.val currently empty
        m_table.push_back(p);
    }

    //loop over the param values in each line
    while (getline(fin, lineBuf)) {
        unsigned int counter = 0;
        istringstream line(lineBuf);
        while (std::getline(line, paramVal, delimiter)) {
            m_table[counter].vals.push_back(stof(paramVal));
            counter++;

        }
    }
}

vector<float> TimeSeries::GetParameterVals(const string &param) const {
    for (auto paramStruct = std::begin(m_table); paramStruct != std::end(m_table); ++paramStruct) {
        if (!paramStruct->name.compare(param)) {
            return paramStruct->vals;
        }
    }
}

vector<float> TimeSeries::GetValuesAtTime(unsigned int zeroBasedTime) {
    vector<float> valuesAtTime;
    for (auto paramStruct = std::begin(m_table); paramStruct != std::end(m_table); ++paramStruct) {
        valuesAtTime.push_back(paramStruct->vals[zeroBasedTime]);
    }
    return valuesAtTime;
}


void TimeSeries::PrintTable() {
    vector<string> names = GetParameters();
    int numOfParams = GetNumOfParameters();
    vector<float> row;
    for (auto paramStruct = std::begin(m_table); paramStruct != std::end(m_table); ++paramStruct) {
        std::cout << (paramStruct->name);
        cout<<"\t";
    }

    cout<<"\n";

    for (int i = 0; i<numOfParams; i++){
        row = GetValuesAtTime(i);
        for (int j=0; j<row.size(); j++)
        {
            cout << row[j];
            cout<<"\t";
            if(j==row.size()-1){
                cout<<"\n";
            }
        }
    }


}


vector<string> TimeSeries::GetParameters() const {
    vector<string> params;
    for (auto paramStruct = std::begin(m_table); paramStruct != std::end(m_table); ++paramStruct) {
        params.push_back(paramStruct->name);
    }
    return params;
}

int TimeSeries::GetNumOfParameters() const {
    int counter = 0;
    for (auto paramStruct = std::begin(m_table); paramStruct != std::end(m_table); ++paramStruct) {
        counter++;
    }
    return counter;
}