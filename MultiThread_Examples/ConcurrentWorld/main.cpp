#include <iostream>
#include <thread>
#include "threadguard.h"
#include "worker.h"
using namespace std;
struct funct {
    int& _refI;
    funct(int& refI) : _refI{refI} {
        // init
    }

    void operator()() const {
        for (int var = 0; var < _refI; ++var) {
            cout << var << " -> " << _refI << endl;
        }
    }
};
int say() {
    cout << "Hello concurrent world " << endl;
    cout << " ------" << endl;
    return 1;
}
int main() {
    thread thread_1{say};
    thread thread_2{Worker(1)};
    thread_1.join();
    thread_2.join();

    int i = 9000;
    funct F1(i);
    thread thread_3{F1};
    // instead of use thread_3.join();
    ThreadGuard guard1{thread_3};
    return 0;
}
