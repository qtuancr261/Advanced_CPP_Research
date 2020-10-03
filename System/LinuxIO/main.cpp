#include <cstdio>
#include <iostream>
#define BUF_SIZE 1024

char buffer[BUF_SIZE];
int main() {
    if (setvbuf(stdout, buffer, _IOFBF, BUF_SIZE) != 0) {
	std::cerr << "Error";
    }
    return 0;
}
