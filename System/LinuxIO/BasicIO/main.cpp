#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include "GenericStructures.h"
const size_t BUF_SIZE{1024};

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
int copyFile(const char* srcFile, const char* destFile) {
	int inputFd{open(srcFile, O_RDONLY)};
	if (inputFd < 0) {
		std::cerr << "File " << srcFile << " not found " << std::endl;
		return -1;
	}

	int outputFd{open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)};
	if (outputFd < 0) {
		std::cerr << "Couldn't create or write to " << destFile << "" << std::endl;
		return -1;
	}

	ssize_t nbytes;
	char buf[BUF_SIZE]{};
	while ((nbytes = read(inputFd, (void*)buf, BUF_SIZE)) > 0) {
		if (write(outputFd, (void*)buf, nbytes) != nbytes) {
			std::cerr << "Error when copy, exit " << std::endl;
			return -2;
		}
	}
	// end of input file
	// last read must be 0
	if (nbytes == -1) {
		std::cerr << "Last read failed, exit " << std::endl;
		return -2;
	}

	if (close(inputFd) == -1) return -3;
	if (close(outputFd) == -1) return -3;

	return 0;
}
int lseekAndDoSt(const char* srcFile, const char* seekParam, const char* stParam) {
	int fd{open(srcFile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)};
	if (fd < 0) return -1;

	off_t offset{atol(seekParam)};
	// ok seek from start of the srcFile
	if (lseek(fd, offset, SEEK_SET) == -1) return -2;
	std::clog << "seed succeeded " << offset << std::endl;
}
int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; ++i) std::cout << argv[i] << std::endl;

	//	std::string app{argv[1]};
	//	if (app == "copy")
	//		copyFile(argv[2], argv[3]);
	//	else if (app == "lseek_io")
	//		lseekAndDoSt(argv[2], argv[3], argv[4]);
	//	else {
	//		std::clog << "copy <srcFile> <destFile>\n lseekAccess <srcFile> <seekOffset> <access> <nbytes> \n";
	//	}

	obj_t headerSrc{10, 20};
	file_gen_t* fileT{new file_gen_t()};

	std::string bufStr("tuantq3");
	fileT->header = headerSrc;

	return 0;
}
