#include  "../../Data/src/file_management.cpp"
#include "../../Model/src/date.cpp"
#include "../../Model/src/time.cpp"
#include "../../Model/src/ticket.cpp"
FileManagement *FileManagement::instance = 0;
int main() {
    std::string maxIdFile = "../../Data/assets/MaxIdFile.txt";
    std::string recordFile = "../../Data/assets/Records.txt";
    cout << recordFile << endl;
    FileManagement *fileManagement = fileManagement->getIntance(recordFile, maxIdFile);
    fileManagement->readMaxIdFromFile();
    cout << "Welcome to  Daewoo (a Bus service) Reservation System" << endl;
    int menuInput;
    std::string name;
    std::string dest;
    std::string dep;
    int id, noTicket, year, month, day, hour, minute;
        
    while(true) {
        cout << "**************************************************" << endl
        << "1 -> Make reservation" << endl
        << "2 -> Modify reservation" << endl
        << "3 -> Cancel reservation" << endl
        << "4 -> Search reservation" << endl
        << "5 -> Quit" << endl;
        cout << "Please enter your choice: ";
        cin >> menuInput;
        switch (menuInput)
        {
        case 1: {
            cout << "Please fill in this information for the Registration" << endl;
            cout << "Passenger Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Departure City: " ;
            getline(cin, dep);
            cout << "Destination City: " ;
            getline(cin, dest);
            cout << "Enter day of travel\n";
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter time of travel\n";
            cout << "Enter hour: ";
            cin >> hour;
            cout << "Enter minute: ";
            cin >> minute;
            cout << "Number of tickets: " ;
            cin >> noTicket;
            Date *date = new Date(year, month, day);
            Time *time = new Time(hour, minute);
            fileManagement->increaseMaxId();
            Ticket reservation(fileManagement->getMaxId(), name, dest, dep, date, time, noTicket);
            fileManagement->insert(&reservation);
        }
        break;
        case 2: {
            cout << "-------------------------------------------------" << endl
                 << "Please fill in this information for updating" << endl;
            cout << "Reservation ID to modify: ";
            cin >> id;
            cout << "Passenger Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Departure City: " ;
            getline(cin, dep);
            cout << "Destination City: " ;
            getline(cin, dest);
            cout << "Enter day of travel\n";
            cout << "Enter day: ";
            cin >> day;
            cout << "Enter month: ";
            cin >> month;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter time of travel\n";
            cout << "Enter hour: ";
            cin >> hour;
            cout << "Enter minute: ";
            cin >> minute;
            cout << "Number of tickets: " ;
            cin >> noTicket;
            Date *date = new Date(year, month, day);
            Time *time = new Time(hour, minute);
            Ticket reservation(id, name, dest, dep, date, time, noTicket);
            cout << "**************************************************" << endl;
            fileManagement->modify(&reservation);
        } 
        break;
        case 3: {
            cout << "Enter rervation ID to cancel: ";
            cin >> id;
            fileManagement->cancel(id);
        }
        break;
        case 4: {
            cout << "Do you want to search by name (n) or date (d): ";
            char options;
            cin >> options;
            
            if(options == 'n') {
                std::string name;
                cout << "Enter passenger name: ";
                cin.ignore();
                getline(cin, name);
                cout << "**************************************************" << endl;
                cout << "\t\t\tYour result\n";
                fileManagement->searchByName(name);
            } else if(options == 'd'){
                cout << "Enter day: ";
                cin >> day;
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;
                Date date(year, month, day);
                cout << "**************************************************" << endl;
                cout << "\t\t\tAll reservation in: " << date.toString() << endl;
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
            cout << "Your choice is invalid, please enter again!" << endl;
        }
            break;
        }
    }
    fileManagement->writeMaxIdToFile();
    return 0;
}