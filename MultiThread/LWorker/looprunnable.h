#ifndef LOOPRUNNABLE_H
#define LOOPRUNNABLE_H

#include <atomic>
#include <condition_variable>
#include <ctime>
#include <iostream>
#include <mutex>
#include "RunnableIf.h"
#include "util.h"

class LoopRunnable : public RunnableIf {
private:
    std::string _name;
    std::condition_variable _event;
    std::mutex _eventMutex;

    std::atomic<bool> _isReqStop;
    std::atomic<bool> _isRunning;
    std::atomic<bool> _isWaitting;
    std::atomic<size_t> _loop;
    std::time_t _startTime;

public:
    LoopRunnable(const std::string& name);
    ~LoopRunnable();

    virtual void runOne() = 0;
    //
    void run() override final;
    bool wait(uint64_t milliSecs);
};

#endif	// LOOPRUNNABLE_H
