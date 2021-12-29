//
// Created by itaye on 29/12/2021.
//

#include "commands.h"

string UploadCommand::getDescription() {
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