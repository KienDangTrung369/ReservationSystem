#include "../include/ticket.h"
int Ticket::getID() {
    return ID;
}
std::string Ticket::getPassengerName() {
    return passengerName;
}
std::string Ticket::getDestination() {
    return destination;
}
std::string Ticket::getDeparture() {
    return departure;
}
Date* Ticket::getDate() const {
    return date;
}
Time* Ticket::getTime() const {
    return time;
}
int Ticket::getNumberOfTickets() {
    return noTickets;
}
Ticket :: Ticket (int ID, std::string passengerName, std::string destination, std::string departure, Date *date, Time *time, int noTickets) {
    this->ID = ID;
    this->passengerName = passengerName;
    this->destination = destination;
    this->departure = departure;
    this->date = date;
    this->time = time;
    this->noTickets = noTickets;
}