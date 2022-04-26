#pragma once
#include <iostream>
#include "date.h"
#include "time.h"
class Ticket {
private:
    int ID;
    int noTickets;
    std::string passengerName;
    std::string destination;
    std::string departure;
    Date *date;
    Time *time;
public:
    Ticket(int _ID, std::string _passengerName, std::string _destination, std::string departure, Date *date, Time *time, int _noTickets);
    int getID();
    std::string getPassengerName();
    std::string getDestination();
    std::string getDeparture();
    Date* getDate() const;
    Time* getTime() const;
    int getNumberOfTickets();
};

