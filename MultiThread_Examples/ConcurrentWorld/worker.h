#ifndef WORKER_H
#define WORKER_H
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class Worker {
private:
    int _id;

public:
    Worker(int id);
    void operator()() const;
};

#endif  // WORKER_H
