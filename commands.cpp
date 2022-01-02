//
// Created by itaye on 29/12/2021.
//

#include "commands.h"

string Command::getDescription() {
    return description;
}

void UploadCommand::execute() {
    DefaultIO* dio = getDio();
    dio->write("Please upload your local train CSV file.\n");
    dio->downloadFile("train");
    dio->write("Upload complete.\n");

    dio->write("Please upload your local test CSV file.\n");
    dio->downloadFile("test");
    dio->write("Upload complete.\n");
}

void SettingCommand::execute() {
    DefaultIO* dio = getDio();
    dio->write("The current correlation threshold is " + to_string(anomalyDetector.getPearThresh()) + "\n");
    dio->write("Type a new threshold\n");
    float newThresh = stof(dio->read());
    while (newThresh < 0 || newThresh > 1){
        dio->write("please choose a value between 0 and 1.\n");
    }
    anomalyDetector.setPearThresh(newThresh);
}

void DetectAnomaliesCommand::execute() {
    DefaultIO* dio = getDio();
    TimeSeries ts("train.csv");
    anomalyDetector.learnNormal(ts);
    *report = anomalyDetector.detect("test.csv");
    lifeTime = anomalyDetector.lifeTime;
    dio->write("anomaly detection complete.\n");
}

void DisplayAnomaliesCommand::execute() {
    DefaultIO* dio = getDio();
    for (auto  it = report->begin(); it != report->end(); ++it) {
        dio->write(to_string(it->timeStep) + "   " + it->description + "\n");
    }
    dio->write("done.\n");
}
void AnalizeResultCommand::setJAnoms() {
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

void AnalizeResultCommand::setRAnomsp() {
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


void AnalizeResultCommand::execute() {
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
    dio->write("True Positive Rate: " + to_string((float)tp/p) + "\n");
    dio->write("False Positive Rate: " + to_string((float)fp/(n)) + "\n");
}


void DefaultIO::downloadFile(string name) {
    string line =read();
    ofstream file;
    file.open(name + ".csv");
    while (line != "done"){
        file << line;
        file << "\n";
        line = read();
    }
    file.close();
}