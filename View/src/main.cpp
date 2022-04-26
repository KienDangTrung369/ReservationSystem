#include "application.cpp"
FileManagement *FileManagement::instance = 0;
int main() {
    std::string maxIdFile = "../../Data/assets/MaxIdFile.txt";
    std::string recordFile = "../../Data/assets/Records.txt";
    Application app(recordFile, maxIdFile);
    app.start();
}