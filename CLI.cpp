//
// Created by itaye on 29/12/2021.
//
#include "CLI.h"

CLI::CLI(DefaultIO* dio):dio(dio) {
    for (int i = 0; i < 6; ++i) {
        cmds[i] = new UploadCommand(dio, "upload a time series csv file");
    }
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
}


CLI::~CLI() {
}


