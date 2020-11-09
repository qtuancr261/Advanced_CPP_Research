/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 19/8/2020
 */
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
	long pageSize{sysconf(_SC_PAGESIZE)};
	std::cout << "Sys page size in byte: " << pageSize << std::endl;
	return 0;
}
