#pragma once
#include <iostream>
#include <fstream>

class Time {
    int hour, minute;
public:
    Time(int hour, int minute);
    std::string toString();
};
