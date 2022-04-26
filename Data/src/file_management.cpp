#include "../include/file_management.h"
#include "../../Model/include/ticket.h"
FileManagement::FileManagement(std::string recordFile, std::string maxIdRecordFile) {
    this->maxID = 0;
    this->recordFile = recordFile;
    this->maxIdRecordFile = maxIdRecordFile;
}
FileManagement * FileManagement ::getIntance(std::string _recordFile, std::string _maxIdRecordFile) {
    if(!instance) {
        instance = new FileManagement(_recordFile, _maxIdRecordFile);
    }
    return instance;
}
void FileManagement :: insert (Ticket *ticket) {
    std::fstream fileOut;

    fileOut.open(recordFile, std::ios::app | std::ios :: out);
    fileOut << ticket->getID() << std::endl;
    fileOut << "Passenger Name: " << ticket->getPassengerName() << std::endl;
    fileOut << "Departure City: " << ticket->getDeparture() << std::endl;
    fileOut << "Destination City: " << ticket->getDestination() << std::endl;
    fileOut << "Day Of Travel: " << ticket->getDate()->toString() << std::endl;
    fileOut << "Time Of Travel: " << ticket->getTime()->toString() << std::endl;
    fileOut << "Number Of Tickets: " << ticket->getNumberOfTickets() << std::endl;

    fileOut.close();
}

void FileManagement :: searchByDate(Date date) {
    std::fstream fileIn;
    fileIn.open(recordFile);
    std::string ID;
    std::string fieldName;
    std::string fieldDestination;
    std::string fieldDeparture;
    std::string fieldDate;
    std::string filedTime;
    std::string fieldNumberOfTickets;
    bool isExist = false;
    if(fileIn.is_open()) {
        while(getline(fileIn, ID)) {
            std::string currentDate;
            std::getline(fileIn, fieldName);
            std::getline(fileIn, fieldDestination);
            std::getline(fileIn, fieldDeparture);
            std::getline(fileIn, fieldDate);
            std::getline(fileIn, filedTime);
            std::getline(fileIn, fieldNumberOfTickets);
            int index = 0;
            while(index < fieldDate.length() && fieldDate[index] != ':') {
                index++;
            }
            index += 2;
            while(index < fieldDate.length()) {
                currentDate += fieldDate[index];
                index++;
            }
            
            if(currentDate == date.toString()) {
                std::cout << "Reservation ID: " << ID << std::endl;
                std::cout << fieldName << std::endl;
                std::cout << fieldDestination << std::endl;
                std::cout << fieldDeparture << std::endl;
                std::cout << fieldDate << std::endl;
                std::cout << filedTime << std::endl;
                std::cout << fieldNumberOfTickets << std::endl;
                std::cout << "-------------------------------------------------" << std::endl;
                isExist = true;
            }
        }
        fileIn.close();
    }
    if(!isExist) {
        std::cout << "Don't exist any reservation in this day!" << std::endl;
    }
}
void FileManagement :: searchByName(const std::string name) {
    std::fstream fileIn;
    fileIn.open(recordFile);
    std::string ID;
    std::string fieldName;
    std::string fieldDestination;
    std::string fieldDeparture;
    std::string fieldDate;
    std::string filedTime;
    std::string fieldNumberOfTickets;
    bool isExist = false;
    if(fileIn.is_open()) {
        while(getline(fileIn, ID)) {
            std::string currentName;
            std::getline(fileIn, fieldName);
            std::getline(fileIn, fieldDestination);
            std::getline(fileIn, fieldDeparture);
            std::getline(fileIn, fieldDate);
            std::getline(fileIn, filedTime);
            std::getline(fileIn, fieldNumberOfTickets);
            int index = 0;
            while(index < fieldName.length() && fieldName[index] != ':') {
                index++;
            }
            index += 2;
            while(index < fieldName.length()) {
                currentName += fieldName[index];
                index++;
            }
            if(currentName == name) {
                std::cout << "Reservation ID: " << ID << std::endl;
                std::cout << fieldName << std::endl;
                std::cout << fieldDestination << std::endl;
                std::cout << fieldDeparture << std::endl;
                std::cout << fieldDate << std::endl;
                std::cout << filedTime << std::endl;
                std::cout << fieldNumberOfTickets << std::endl;
                std::cout << "-------------------------------------------------" << std::endl;
                isExist = true;
            }
        }
        fileIn.close();
    }
    if(!isExist) {
        std::cout << "Don't exist this name!" << std::endl;
    }
}
void FileManagement :: cancel(int ID) {
    std::ifstream fileIn;
    std::fstream fileOut;
    std::string record;
    int currentID = 0;
    bool isExist = false;
    
    fileIn.open(recordFile);
    fileOut.open("temp.txt", std::ios::app | std::ios :: out);
    if(fileIn.is_open()) {
        while(getline(fileIn, record)) {
            currentID = stoi(record);
            if(currentID == ID) {
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                }
                isExist = true;
            } else {
                fileOut << currentID << std::endl;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                    fileOut << record << std::endl;
                }
            }
        }
    }
    fileIn.close();
    fileOut.close();

    if(!isExist) {
        std::cout << "Reservation could not be found!" << std::endl;
        remove("temp.txt");
    } else {
        remove(recordFile.c_str());
        int ret = rename("temp.txt", recordFile.c_str());
        if(ret != 0) {
            perror("Error");
        }
    }
}
void FileManagement :: modify(Ticket *newTicket) {
    std::ifstream fileIn;
    std::fstream fileOut;

    fileIn.open(recordFile);
    fileOut.open("temp.txt", std::ios::app | std::ios :: out);
    std::string record;
    bool updated = false;
    int currentID = 0;
    if(fileIn.is_open()) {
        while(std::getline(fileIn, record)) {
            currentID = stoi(record);
            if(currentID == newTicket->getID()) {
                fileOut << currentID << std::endl;
                fileOut << "Passenger Name: " << newTicket->getPassengerName() << std::endl;
                fileOut << "Departure City: " << newTicket->getDeparture() << std::endl;
                fileOut << "Destination City: " << newTicket->getDestination() << std::endl;
                fileOut << "Day Of Travel: " << newTicket->getDate()->toString() << std::endl;
                fileOut << "Time Of Travel: " << newTicket->getTime()->toString() << std::endl;
                fileOut << "Number Of Tickets: " << newTicket->getNumberOfTickets() << std::endl;
                updated = true;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    std::getline(fileIn, record);
                }
                std::cout << "Record updated" << std::endl;
            } else {
                fileOut << currentID << std::endl;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    std::getline(fileIn, record);
                    fileOut << record << std::endl;
                }
            }
        }
    }
    fileIn.close();
    fileOut.close();
    if(!updated) {
        std::cout << "Record could not be found!" << std::endl;
        remove("temp.txt");
    } else {
        remove(recordFile.c_str());
        int ret = rename("temp.txt", recordFile.c_str());
        if(ret != 0) {
            perror("Error");
        }
    }
}

void FileManagement :: readMaxIdFromFile() {
    std::ifstream fileIn;
    fileIn.open(maxIdRecordFile);
    if(fileIn.is_open()) {
        while(fileIn >> maxID) {
        }
    }
    fileIn.close();
}

void FileManagement::writeMaxIdToFile() {
    std::fstream fileOut;
    fileOut.open(maxIdRecordFile, std::ios :: out);
    fileOut << maxID;
}

void FileManagement::increaseMaxId() {
    maxID++;
}

int FileManagement::getMaxId() {
    return maxID;
}
