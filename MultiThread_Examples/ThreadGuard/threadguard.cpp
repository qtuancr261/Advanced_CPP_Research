#include "threadguard.h"


ThreadGuard::ThreadGuard(std::thread &srcThread)
    : guardedThread{srcThread}
{
    // ThreadGuard constructor
}

ThreadGuard::~ThreadGuard()
{
    if (guardedThread.joinable())
        guardedThread.join();
}
