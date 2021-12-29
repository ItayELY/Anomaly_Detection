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
    float newThresh = stof(dio->read());
    while (newThresh < 0 || newThresh > 1){
        dio->write("please choose a value between 0 and 1.”\n");
    }
    anomalyDetector.setPearThresh(newThresh);
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