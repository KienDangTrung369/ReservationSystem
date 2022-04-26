#include  "../../Data/src/file_management.cpp"
#include "../../Model/src/date.cpp"
#include "../../Model/src/time.cpp"
#include "../../Model/src/ticket.cpp"
class Application {
private:
    std::string maxIdFile;
    std::string recordFile;
    FileManagement *fileManagement;
    void displayMenu();
    void displaySearchOption();
    void getInput();
public:
    Application(std::string recordFile, std::string maxIdFile);
    void start();
};