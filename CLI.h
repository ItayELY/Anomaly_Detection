//Itay Elyashev 212356364
//Yonadav Leibowitz 207424490

#ifndef ANOMALY_DETECTION_CLI_H
#define ANOMALY_DETECTION_CLI_H

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    // you can add data members
    Command* cmds[5];
    HybridAnomalyDetector anomalyDetector;
    vector<AnomalyReport> report;
public:
    CLI(DefaultIO* dio);
    void printMenu();
    void start();
    virtual ~CLI();
};

#endif //ANOMALY_DETECTION_CLI_H
