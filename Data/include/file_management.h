#pragma once
#include <iostream>
#include <fstream>
#include "../../Model/include/date.h"
#include "../../Model/include/ticket.h"
#include "../../Model/include/time.h"


#define NUMBER_OF_FIELDS 7

// use singleton design pattern
class FileManagement {
    static FileManagement *instance;
    std::string recordFile;
    std::string maxIdRecordFile;
    int maxID;
    FileManagement(std::string recordFile, std::string maxIdRecordFile);
public:
    static FileManagement *getIntance(std::string _recordFile, std::string _maxIdRecordFile);
    int getMaxId();
    void readMaxIdFromFile();
    void writeMaxIdToFile();
    void increaseMaxId();
    void modify(Ticket *newRervation);
    void cancel(int ID);
    void insert(Ticket *reservation);
    void searchByName(const std::string name);
    void searchByDate(Date date); 
};