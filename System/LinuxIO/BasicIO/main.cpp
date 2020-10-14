#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;
void init(const std::string& path) {
    int fd{open(path.c_str(), O_RDWR)};
    if (fd < 0) {
        std::cerr << "File doesn't exist: " << path << std::endl;
        std::clog << "Creating now ..." << std::endl;
        fd = open(path.c_str(), O_RDWR | O_CREAT, S_IRWXU);
    }
    struct stat fileStat;
    fstat(fd, &fileStat);
    std::cout << "device id " << fileStat.st_dev << std::endl;
    std::cout << "file size " << fileStat.st_size << std::endl;
    close(fd);
}
int main() {
    cout << "Hello World!" << endl;
    std::string fileName = "data.ini";
    init(fileName);
    return 0;
}
