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
    for (auto it = m_table.begin(); it != m_table.end(); ++it) {
        if (!it->name.compare(param)) {
            return it->vals;
        }
    }
    return vector<float>();
}

vector<float> TimeSeries::GetValuesAtTime(unsigned int oneBasedTime) {
    vector<float> valuesAtTime;
    for (auto it = m_table.begin(); it != m_table.end(); ++it) {
        valuesAtTime.push_back(it->vals[oneBasedTime]);
    }
    return valuesAtTime;
}

float TimeSeries::GetValuesOfFeatureAtTime(unsigned int oneBasedTime, const string& param) const{
    for (auto it = m_table.begin(); it != m_table.end(); ++it) {
        if (!it->name.compare(param)) {
            return it->vals[oneBasedTime];
        }
    }
}


void TimeSeries::PrintTable() {
    int numOfParams = GetNumOfParameters();
    vector<float> row;
    for (auto it = m_table.begin(); it != m_table.end(); ++it) {
        std::cout << (it->name);
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


vector<string> TimeSeries::GetParameterNames() const {
    vector<string> params;
    for (auto it = m_table.begin(); it != m_table.end(); ++it) {
        params.push_back(it->name);
    }
    return params;
}

unsigned int TimeSeries::GetNumOfParameters() const {
    return m_table.size();
}

unsigned int TimeSeries::GetTimeOfLife() const {
    return m_table[0].vals.size();
}