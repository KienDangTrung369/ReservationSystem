#include "../include/date.h"
Date :: Date(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}
std::string Date :: toString() {
    std::string dateToString = "";
    if(day < 10) dateToString += "0";
    else dateToString += std::to_string(day);
    dateToString += "/";
    if(month < 10) dateToString += "0";
    dateToString += std::to_string(month);
    dateToString += "/";
    dateToString += std::to_string(year);
    return dateToString;
}