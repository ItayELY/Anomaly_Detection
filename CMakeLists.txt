cmake_minimum_required(VERSION 3.20)
project(Anomaly_Detection)

set(CMAKE_CXX_STANDARD 11)

#add_executable(Anomaly_Detection anomaly_detection_util.cpp MainTrain.cpp)
add_executable(Anomaly_Detection timeseries.cpp main.cpp)
