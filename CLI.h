//
// Created by itaye on 29/12/2021.
//

#ifndef ANOMALY_DETECTION_CLI_H
#define ANOMALY_DETECTION_CLI_H

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    // you can add data members
    Command* cmds[6];
    HybridAnomalyDetector anomalyDetector;
public:
    CLI(DefaultIO* dio);
    void printMenu();
    void start();
    virtual ~CLI();
};

#endif //ANOMALY_DETECTION_CLI_H
