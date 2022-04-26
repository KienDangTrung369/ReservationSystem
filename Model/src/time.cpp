#include "../include/time.h"
Time::Time(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
}
std::string Time ::toString() {
    std::string timeToString = "";
    if(hour < 10) timeToString = "0";
    timeToString += std::to_string(hour);
    timeToString += ":";
    if(minute < 10) timeToString += "0";
    timeToString += std::to_string(minute);
    return timeToString;
}