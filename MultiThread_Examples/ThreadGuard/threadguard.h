#ifndef THREADGUARD_H
#define THREADGUARD_H
#include<thread>
using std::thread;
class ThreadGuard final
{
private:
    thread& guardedThread;
public:
    explicit ThreadGuard(thread& srcThread);
    ThreadGuard(const thread& srcThread) = delete;
    ThreadGuard& operator=(const thread& srcThread) const = delete;
    ~ThreadGuard();
};

#endif // THREADGUARD_H
