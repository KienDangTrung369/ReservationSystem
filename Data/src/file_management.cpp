#include "../include/file_management.h"
#include "../../Model/include/ticket.h"
using namespace std;
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
    fileOut << ticket->getID() << endl;
    fileOut << "Passenger Name: " << ticket->getPassengerName() << endl;
    fileOut << "Departure City: " << ticket->getDeparture() << endl;
    fileOut << "Destination City: " << ticket->getDestination() << endl;
    fileOut << "Day Of Travel: " << ticket->getDate()->toString() << endl;
    fileOut << "Time Of Travel: " << ticket->getTime()->toString() << endl;
    fileOut << "Number Of Tickets: " << ticket->getNumberOfTickets() << endl;

    fileOut.close();
}

void FileManagement :: searchByDate(Date date) {
    fstream fileIn;
    fileIn.open(recordFile);
    string ID;
    string fieldName;
    string fieldDestination;
    string fieldDeparture;
    string fieldDate;
    string filedTime;
    string fieldNumberOfTickets;
    bool isExist = false;
    if(fileIn.is_open()) {
        while(getline(fileIn, ID)) {
            string currentDate;
            getline(fileIn, fieldName);
            getline(fileIn, fieldDestination);
            getline(fileIn, fieldDeparture);
            getline(fileIn, fieldDate);
            getline(fileIn, filedTime);
            getline(fileIn, fieldNumberOfTickets);
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
                cout << "Reservation ID: " << ID << endl;
                cout << fieldName << endl;
                cout << fieldDestination << endl;
                cout << fieldDeparture << endl;
                cout << fieldDate << endl;
                cout << filedTime << endl;
                cout << fieldNumberOfTickets << endl;
                cout << "-------------------------------------------------" << endl;
                isExist = true;
            }
        }
        fileIn.close();
    }
    if(!isExist) {
        cout << "Don't exist any reservation in this day!" << endl;
    }
}
void FileManagement :: searchByName(const string name) {
    fstream fileIn;
    fileIn.open(recordFile);
    string ID;
    string fieldName;
    string fieldDestination;
    string fieldDeparture;
    string fieldDate;
    string filedTime;
    string fieldNumberOfTickets;
    bool isExist = false;
    if(fileIn.is_open()) {
        while(getline(fileIn, ID)) {
            string currentName;
            getline(fileIn, fieldName);
            getline(fileIn, fieldDestination);
            getline(fileIn, fieldDeparture);
            getline(fileIn, fieldDate);
            getline(fileIn, filedTime);
            getline(fileIn, fieldNumberOfTickets);
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
                cout << "Reservation ID: " << ID << endl;
                cout << fieldName << endl;
                cout << fieldDestination << endl;
                cout << fieldDeparture << endl;
                cout << fieldDate << endl;
                cout << filedTime << endl;
                cout << fieldNumberOfTickets << endl;
                cout << "-------------------------------------------------" << endl;
                isExist = true;
            }
        }
        fileIn.close();
    }
    if(!isExist) {
        cout << "Don't exist this name!" << endl;
    }
}
void FileManagement :: cancel(int ID) {
    ifstream fileIn;
    fstream fileOut;
    string record;
    int currentID = 0;
    bool isExist = false;
    
    fileIn.open(recordFile);
    fileOut.open("temp.txt", ios::app | ios :: out);
    if(fileIn.is_open()) {
        while(getline(fileIn, record)) {
            currentID = stoi(record);
            if(currentID == ID) {
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                }
                isExist = true;
            } else {
                fileOut << currentID << endl;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                    fileOut << record << endl;
                }
            }
        }
    }
    fileIn.close();
    fileOut.close();

    if(!isExist) {
        cout << "Reservation could not be found!" << endl;
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
    ifstream fileIn;
    fstream fileOut;

    fileIn.open(recordFile);
    fileOut.open("temp.txt", ios::app | ios :: out);
    string record;
    bool updated = false;
    int currentID = 0;
    if(fileIn.is_open()) {
        while(getline(fileIn, record)) {
            currentID = stoi(record);
            if(currentID == newTicket->getID()) {
                fileOut << currentID << endl;
                fileOut << "Passenger Name: " << newTicket->getPassengerName() << endl;
                fileOut << "Departure City: " << newTicket->getDeparture() << endl;
                fileOut << "Destination City: " << newTicket->getDestination() << endl;
                fileOut << "Day Of Travel: " << newTicket->getDate()->toString() << endl;
                fileOut << "Time Of Travel: " << newTicket->getTime()->toString() << endl;
                fileOut << "Number Of Tickets: " << newTicket->getNumberOfTickets() << endl;
                updated = true;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                }
                cout << "Record updated" << endl;
            } else {
                fileOut << currentID << endl;
                for(int i = 0; i < NUMBER_OF_FIELDS - 1; i++) {
                    getline(fileIn, record);
                    fileOut << record << endl;
                }
            }
        }
    }
    fileIn.close();
    fileOut.close();
    if(!updated) {
        cout << "Record could not be found!" << endl;
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
