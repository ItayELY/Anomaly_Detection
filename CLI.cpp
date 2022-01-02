//
// Created by itaye on 29/12/2021.
//
#include "CLI.h"

CLI::CLI(DefaultIO* dio):dio(dio) {
    int lifeTime = 0;
    cmds[0] = new UploadCommand(dio, "upload a time series csv file");
    cmds[1] = new SettingCommand(dio, "algorithm settings", anomalyDetector);
    cmds[2] = new DetectAnomaliesCommand(dio, "detect anomalies", anomalyDetector,
                                         report, lifeTime);
    cmds[3] = new DisplayAnomaliesCommand(dio, "display results",report);
    cmds[4] = new AnalizeResultCommand(dio, "upload anomalies and analyze results",report,
                                       anomalyDetector);
}

void CLI::printMenu() {
    dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
    for (int i = 0; i < 5; ++i) {
        dio->write(i+1);
        dio->write("." + (cmds[i])->getDescription() + "\n");
    }
    dio->write("6.exit\n");
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
            choice = "3";
        }
        if (choice == "4"){
            cmds[3]->execute();
        }
        if (choice == "5"){
            cmds[4]->execute();
        }
        printMenu();
        choice = dio->read();
    }

}


CLI::~CLI() {
}


