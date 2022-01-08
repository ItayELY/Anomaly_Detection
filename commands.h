//Itay Elyashev 212356364
//Yonadav Leibowitz 207424490

#ifndef ANOMALY_DETECTION_COMMANDS_H
#define ANOMALY_DETECTION_COMMANDS_H
#include<iostream>
#include <string.h>

#include <fstream>
#include <sstream>

#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

struct PositiveAnomaly
{
    float start, end;
    bool isFalse = true;
};

struct JoinedAnomaly
{
    string description;
    float start, end;
};

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here
    void downloadFile(string name){
        string line =read();
        ofstream file;
        file.open(name + ".csv");
        while (line != "done\n"){
            file << line;
            line = read();
        }
        file.close();
    }
};

// you may add here helper classes


// you may edit this class
class Command{
    DefaultIO* dio;
    string description;
public:
    Command(DefaultIO* dio, string description):dio(dio), description(description){}
    string getDescription(){
        return description;
    }
    DefaultIO* getDio(){return  dio;}
    virtual void execute()=0;
    virtual ~Command(){}
};

// implement here your command classes
class UploadCommand: public Command{
public:
    UploadCommand(DefaultIO* dio, string description): Command(dio, description){};

    void execute(){
        DefaultIO* dio = getDio();
        dio->write("Please upload your local train CSV file.\n");
        dio->downloadFile("train");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->downloadFile("test");
        dio->write("Upload complete.\n");
        //dio->write("Upload complete.\n");
    }
};

class SettingCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
public:
    SettingCommand(DefaultIO* dio, string description, HybridAnomalyDetector anomalyDetector):
        Command(dio, description), anomalyDetector(anomalyDetector){};
    void execute(){
        DefaultIO* dio = getDio();
        dio->write("The current correlation threshold is " + to_string(anomalyDetector.getPearThresh()) + "\n");
        dio->write("Type a new threshold\n");
        float newThresh = stof(dio->read());
        while (newThresh < 0 || newThresh > 1){
            dio->write("please choose a value between 0 and 1.\n");
        }
        anomalyDetector.setPearThresh(newThresh);
    }
};

class DetectAnomaliesCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
    vector<AnomalyReport>* report;
    int lifeTime;
public:
    DetectAnomaliesCommand(DefaultIO* dio, string description, HybridAnomalyDetector anomalyDetector,
                           vector<AnomalyReport>* report, int& lifeTime):
    Command(dio, description), anomalyDetector(anomalyDetector), report(report), lifeTime(lifeTime){};
    void execute(){
        DefaultIO* dio = getDio();
        TimeSeries ts("train.csv");
        anomalyDetector.learnNormal(ts);
        *report = anomalyDetector.detect("test.csv");
        lifeTime = anomalyDetector.lifeTime;
        dio->write("anomaly detection complete.\n");

    }
};

class DisplayAnomaliesCommand: public Command{
    vector<AnomalyReport>* report;
public:
    DisplayAnomaliesCommand(DefaultIO* dio, string description, vector<AnomalyReport>& report):
            Command(dio, description), report(&report){};
    void execute(){
        DefaultIO* dio = getDio();
        for (auto  it = report->begin(); it != report->end(); ++it) {
            dio->write(to_string(it->timeStep) + "   " + it->description + "\n");
        }
        dio->write("done.\n");
    }
};

class AnalizeResultCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
    vector<PositiveAnomaly> rAnoms;
    vector<JoinedAnomaly> jAnoms;
    vector<AnomalyReport>* report;
    int n = 0, N = 0, p = 0, anomTime = 0, tp = 0, fp = 0;
public:
    AnalizeResultCommand(DefaultIO* dio, string description, vector<AnomalyReport>& report,
                         HybridAnomalyDetector anomalyDetector): Command(dio, description), report(&report),
                         anomalyDetector(anomalyDetector){}
    void setRAnomsp(){
        // File pointer
        ifstream fin;
        // Open an existing file
        fin.open("positives.csv");

        string lineBuf;
        char delimiter = ',';
        string startTime;
        string endTime;

        //read first line

        while(getline(fin, lineBuf)){
            istringstream line(lineBuf);
            PositiveAnomaly pAnom;

            std::getline(line, startTime, delimiter);
            pAnom.start = stoi(startTime);

            std::getline(line, endTime, delimiter);
            pAnom.end= stoi(endTime);

            this->rAnoms.push_back(pAnom);
            this->p++;
            this->anomTime+=(pAnom.end-pAnom.start);
        }
        N = n - anomTime;
    }
    void setJAnoms(){
        for (auto  it = report->begin(); it != report->end(); ++it) {
            string desc = it->description;
            int start = it->timeStep, end = it->timeStep;
            ++it;
            if (it == report->end()){
                break;
            }
            bool flag = false;
            while (it->description == desc){
                end = it->timeStep;
                ++it;
                if (it == report->end()){
                    flag = true;
                    break;
                }
            }
            JoinedAnomaly janom;
            janom.start = start;
            janom.end = end;
            janom.description = desc;
            this->jAnoms.push_back(janom);
            if (flag){
                break;
            }
        }
    }
    void execute(){
        anomalyDetector.detect("test.csv");
        anomTime = 0;
        p = 0;
        fp = 0;
        tp = 0;
        n = anomalyDetector.lifeTime;
        jAnoms.clear();
        rAnoms.clear();
        DefaultIO* dio = getDio();
        dio->write("Please upload your local anomalies file.\n");
        dio->downloadFile("positives");
        dio->write("Upload complete.\n");
        AnalizeResultCommand::setJAnoms();
        AnalizeResultCommand::setRAnomsp();
        for (int i = 0; i < jAnoms.size(); ++i) {
            bool flag = false;
            for (int j = 0; j < rAnoms.size(); ++j) {
                if(jAnoms[i].start >= rAnoms[j].start){
                    if(jAnoms[i].start <= rAnoms[j].end){
                        tp++;
                        flag = true;
                        break;
                    }
                }
                if(rAnoms[j].start >= jAnoms[i].start){
                    if(rAnoms[j].start <= jAnoms[i].end){
                        tp++;
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag){
                fp++;
            }
        }

        string strTrue = to_string((float)tp/p);
        while (strTrue[strTrue.size() - 1] == '0' || strTrue[strTrue.size() - 1] == '.'){
            if(strTrue[strTrue.size() - 1] == '.'){
                strTrue.resize(strTrue.size() - 1);
                break;
            }
            strTrue.resize(strTrue.size() - 1);
        }

        string strFalse = to_string((float)fp/(n));
        while (strFalse[strFalse.size() - 1] == '0' || strFalse[strFalse.size() - 1] == '.'){
            if(strFalse[strFalse.size() - 1] == '.'){
                strFalse.resize(strFalse.size() - 1);
                break;
            }
            strFalse.resize(strFalse.size() - 1);
        }
        dio->write("True Positive Rate: " + strTrue + "\n");
        dio->write("False Positive Rate: " + strFalse + "\n");
    }

};



#endif //ANOMALY_DETECTION_COMMANDS_H
