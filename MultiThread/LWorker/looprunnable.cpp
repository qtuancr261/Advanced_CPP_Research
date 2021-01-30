#include "looprunnable.h"

LoopRunnable::LoopRunnable(const std::string& name)
    : _name{name}
    , _isReqStop{false}
    , _isRunning{false}
    , _isWaitting{false}
    , _loop(0)
    , _startTime{0} {}

LoopRunnable::~LoopRunnable() {}

void LoopRunnable::run() {
    _startTime = std::time(nullptr);
    // std::clog << "Thread " << _name << " started \n";
    printDebug(LoopRunnalbe::run, " Thread started");
    _isRunning.exchange(true);
    try {
        while (_isRunning.load()) {
            runOne();
            ++_loop;
        }
    } catch (const std::exception& excep) {
        printDebug(LoopRunnable::run, excep.what());
    }

    _isRunning.exchange(false);
    printDebug(LoopRunnable::run, "Thread exit");
}

bool LoopRunnable::wait(uint64_t milliSecs) {
    if (_isWaitting.exchange(true) == true) {
        printDebug(LoopRunnable::wait, "Another thread is waiting, exit ...");
        return false;
    }

    std::unique_lock<std::mutex> lock{_eventMutex};
}
