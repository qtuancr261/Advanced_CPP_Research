#ifndef LOOPRUNNABLE_H
#define LOOPRUNNABLE_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include "RunnableIf.h"
class LoopRunnable : public RunnableIf {
private:
    std::string _name;
    std::condition_variable _event;
    std::mutex _eventMutex;

    std::atomic<bool> _isReqStop;
    std::atomic<bool> _isRunning;
    std::atomic<bool> _isWaitting;
    std::atomic<size_t> _loop;

public:
    LoopRunnable(const std::string& name);
    ~LoopRunnable();
    void run() override;
};

#endif  // LOOPRUNNABLE_H
