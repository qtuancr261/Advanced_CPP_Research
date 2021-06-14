/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 16/4/2020
 */
#include <iostream>
#include <vector>
#include "Poco/MemoryPool.h"

void testFunct(char (&a)[10]) {
	std::cout << typeid(a).name();
}
using namespace std;

struct Job {
	int* ptr;
	std::vector<int> data;
	Job(int* srcPtr, std::vector<int>& srcData)
		: ptr{srcPtr} {
		data.swap(srcData);
	}

	void use() {
		std::cout << *ptr << std::endl;
		std::cout << "Data size " << data.size() << std::endl;
	}

	~Job() {
		std::clog << "Call ~Job()" << std::endl;
	}
};

int main() {
	Poco::MemoryPool memPool(sizeof(Job), 10, 0);
	// prepare data
	std::vector<int> data{10, 11, 12, 13};
	int* ptr{new int(1996)};
	// placement new with specific mem area (mem pool)
	void* newMem = memPool.get();
	std::clog << "Mempool size" << memPool.available() << std::endl;
	Job* newJob = new (newMem) Job(ptr, data);
	// do something
	newJob->use();
	// ADVICE: EXPLICITLY call placed object's destructor afer using it
	newJob->~Job();
	// DO NOT call delete newJob
	memPool.release(newJob);
	std::clog << "Mempool size" << memPool.available() << std::endl;
}
