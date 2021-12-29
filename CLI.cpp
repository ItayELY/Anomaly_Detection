//
// Created by itaye on 29/12/2021.
//
#include "CLI.h"

CLI::CLI(DefaultIO* dio):dio(dio) {
    for (int i = 0; i < 6; ++i) {
        cmds[i] = new UploadCommand(dio, "upload a time series csv file");
    }
    cmds[1] = new SettingCommand(dio, "algorithm settings", this->anomalyDetector);
    cmds[2] = new DetectAnomaliesCommand(dio, "detect anomalies", this->anomalyDetector);
}

void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    for (int i = 0; i < 6; ++i) {
        dio->write(i+1);
        dio->write(". " + (cmds[i])->getDescription() + "\n");
    }
}

void CLI::start(){
    printMenu();
    string choice = dio->read();
    while(choice != "6"){
        if (choice == "1"){
            cmds[0]->execute();
        }
        if (choice == "2"){
            cmds[1]->execute();
        }
        if (choice == "3"){
            cmds[2]->execute();
        }
        printMenu();
        choice = dio->read();
    }

}


CLI::~CLI() {
}


