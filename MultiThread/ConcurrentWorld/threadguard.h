#ifndef THREADGUARD_H
#define THREADGUARD_H
#include <thread>
using std::thread;
class ThreadGuard {
private:
    thread& _guardThread;

public:
    explicit ThreadGuard(thread& srcThread);
    ~ThreadGuard();
    ThreadGuard(const thread& srcThread) = delete;
    ThreadGuard& operator=(const thread& srcThread) = delete;
};

#endif  // THREADGUARD_H
