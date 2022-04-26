#pragma once
#include <iostream>

class Date {
    int year, month, day;
public:
    Date(int year, int month, int day);
    std::string toString();
};
