//
// Created by itaye on 29/12/2021.
//

#ifndef ANOMALY_DETECTION_COMMANDS_H
#define ANOMALY_DETECTION_COMMANDS_H
#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here
    void downloadFile(string name);
};

// you may add here helper classes


// you may edit this class
class Command{
    DefaultIO* dio;
    string description;
public:
    Command(DefaultIO* dio, string description):dio(dio), description(description){}
    string getDescription();
    DefaultIO* getDio(){return  dio;}
    virtual void execute()=0;
    virtual ~Command(){}
};

// implement here your command classes
class UploadCommand: public Command{
public:
    UploadCommand(DefaultIO* dio, string description): Command(dio, description){};

    void execute();
};

class SettingCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
public:
    SettingCommand(DefaultIO* dio, string description, HybridAnomalyDetector anomalyDetector):
        Command(dio, description), anomalyDetector(anomalyDetector){};
    void execute();
};

class DetectAnomaliesCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
public:
    DetectAnomaliesCommand(DefaultIO* dio, string description, HybridAnomalyDetector anomalyDetector):
    Command(dio, description), anomalyDetector(anomalyDetector){};
    void execute();
};

class DisplayAnomaliesCommand: public Command{
    HybridAnomalyDetector anomalyDetector;
public:
    DisplayAnomaliesCommand(DefaultIO* dio, string description, HybridAnomalyDetector anomalyDetector):
            Command(dio, description), anomalyDetector(anomalyDetector){};
    void execute();
};
#endif //ANOMALY_DETECTION_COMMANDS_H
