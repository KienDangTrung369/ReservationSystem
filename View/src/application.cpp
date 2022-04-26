#include "../include/application.h"

Application::Application(std::string recordFile, std::string maxIdFile) {
    this->maxIdFile = maxIdFile;
    this->recordFile = recordFile;
    this->fileManagement = fileManagement->getIntance(recordFile, maxIdFile);
}

void Application::displayMenu() {
    std::cout << "**************************************************" << std::endl
         << "1 -> Make reservation" << std::endl
         << "2 -> Modify reservation" << std::endl
         << "3 -> Cancel reservation" << std::endl
         << "4 -> Search reservation" << std::endl
         << "5 -> Quit" << std::endl;
    std::cout << "Please enter your choice: ";
}

void Application::start() {
    std::string name;
    std::string dest;
    std::string dep;
    int id, noTicket, year, month, day, hour, minute;
    int menuInput = 0;
    fileManagement->readMaxIdFromFile();
    while(true) {
        displayMenu();
        std::cin >> menuInput;
        switch (menuInput)
        {
        case 1: {
            std::cout << "Please fill in this information for the Registration" << std::endl;
            std::cout << "Passenger Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Departure City: " ;
            std::getline(std::cin, dep);
            std::cout << "Destination City: " ;
            std::getline(std::cin, dest);
            std::cout << "Enter day of travel\n";
            std::cout << "Enter day: ";
            std::cin >> day;
            std::cout << "Enter month: ";
            std::cin >> month;
            std::cout << "Enter year: ";
            std::cin >> year;
            std::cout << "Enter time of travel\n";
            std::cout << "Enter hour: ";
            std::cin >> hour;
            std::cout << "Enter minute: ";
            std::cin >> minute;
            std::cout << "Number of tickets: " ;
            std::cin >> noTicket;
            Date *date = new Date(year, month, day);
            Time *time = new Time(hour, minute);
            fileManagement->increaseMaxId();
            Ticket reservation(fileManagement->getMaxId(), name, dest, dep, date, time, noTicket);
            fileManagement->insert(&reservation);
        }
        break;
        case 2: {
            std::cout << "-------------------------------------------------" << std::endl
                 << "Please fill in this information for updating" << std::endl;
            std::cout << "Reservation ID to modify: ";
            std::cin >> id;
            std::cout << "Passenger Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Departure City: " ;
            std::getline(std::cin, dep);
            std::cout << "Destination City: " ;
            std::getline(std::cin, dest);
            std::cout << "Enter day of travel" << std::endl;
            std::cout << "Enter day: ";
            std::cin >> day;
            std::cout << "Enter month: ";
            std::cin >> month;
            std::cout << "Enter year: ";
            std::cin >> year;
            std::cout << "Enter time of travel" << std::endl;
            std::cout << "Enter hour: ";
            std::cin >> hour;
            std::cout << "Enter minute: ";
            std::cin >> minute;
            std::cout << "Number of tickets: " ;
            std::cin >> noTicket;
            Date *date = new Date(year, month, day);
            Time *time = new Time(hour, minute);
            Ticket reservation(id, name, dest, dep, date, time, noTicket);
            std::cout << "**************************************************" << std::endl;
            fileManagement->modify(&reservation);
        } 
        break;
        case 3: {
            std::cout << "Enter rervation ID to cancel: ";
            std::cin >> id;
            fileManagement->cancel(id);
        }
        break;
        case 4: {
            std::cout << "Do you want to search by name (n) or date (d): ";
            char options;
            std::cin >> options;
            
            if(options == 'n') {
                std::string name;
                std::cout << "Enter passenger name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "**************************************************" << std::endl;
                std::cout << "\t\t\tYour result\n";
                fileManagement->searchByName(name);
            } else if(options == 'd'){
                std::cout << "Enter day: ";
                std::cin >> day;
                std::cout << "Enter month: ";
                std::cin >> month;
                std::cout << "Enter year: ";
                std::cin >> year;
                Date date(year, month, day);
                std::cout << "**************************************************" << std::endl;
                std::cout << "\t\t\tAll reservation in: " << date.toString() << std::endl;
                fileManagement->searchByDate(date); 
            }
        }
        break;
        case 5: {
            fileManagement->writeMaxIdToFile();
            exit(0);
        }
        break;
        default: {
            std::cout << "Your choice is invalid, please enter again!" << std::endl;
        }
            break;
        }
    }
}