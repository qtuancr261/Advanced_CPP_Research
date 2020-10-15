#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "GenericStructures.h"
using namespace std;
void init(const std::string& path) {
	int fd{open(path.c_str(), O_RDWR)};
	if (fd < 0) {
		std::cerr << "File doesn't exist: " << path << std::endl;
		std::clog << "Creating now ..." << std::endl;
		fd = open(path.c_str(), O_RDWR | O_CREAT, S_IRWXU);
		fallocate(fd, 0, 0, sizeof(generic_info_t));
	}
	struct stat fileStat;
	fstat(fd, &fileStat);
	std::cout << "device id " << fileStat.st_dev << std::endl;
	std::cout << "file size " << fileStat.st_size << std::endl;
	// mapping
	generic_info_t* newGenInfoPtr;
	newGenInfoPtr = (generic_info_t*)mmap(NULL, sizeof(generic_info_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
}
int main() {
	cout << "Hello World!" << endl;
	std::string fileName = "data.ini";
	init(fileName);
	return 0;
}
