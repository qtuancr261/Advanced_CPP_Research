#ifndef LOOPRUNNABLE_H
#define LOOPRUNNABLE_H

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <iostream>
#include <mutex>
#include "RunnableIf.h"
#include "util.h"
using namespace std::chrono_literals;
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
    // loop operations
    void run() override final;
    bool wait(uint64_t milliSecs);
    bool breakWait();
    void reqStop(bool reqBreakWait = false);

    // reset all
    LoopRunnable& reset();

    // loop info
    bool isRunning() const;
    bool isWaiting() const;
    size_t getNLoop() const;
    std::string getName() const;
    std::time_t getStartTime() const;
};

#endif	// LOOPRUNNABLE_H
