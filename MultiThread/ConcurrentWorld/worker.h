#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include <numeric>
#include <thread>
using std::accumulate;
using std::cin;
using std::cout;
using std::endl;
using std::thread;
class Worker {
private:
    int _id;

public:
    Worker(int id);
    void operator()() const;
    template <typename Iterator, typename T>
    static void calculateSum(Iterator first, Iterator last, T& result) {
        // this->operator()();
        result = accumulate(first, last, 0);
        //
        std::clog << "Thread id " << std::this_thread::get_id() << " calculated result: " << result << " - on CPU " << sched_getcpu() << std::endl;
    }
};

#endif	// WORKER_H
