#include <iostream>
#include "timeseries.h"


int main() {
    TimeSeries* table = new TimeSeries("readTest.csv");
    table->GetParameterVals("height");
    table->GetValuesAtTime(0);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
