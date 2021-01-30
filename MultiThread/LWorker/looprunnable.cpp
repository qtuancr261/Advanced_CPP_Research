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
    if (_event.wait_for(lock, std::chrono::milliseconds(milliSecs)) == std::cv_status::timeout) {
        _isWaitting.exchange(false);
        printDebug(LoopRunnable::wait, "wait_for timeout");
        return false;
    }
    return true;
}

bool LoopRunnable::breakWait() {
    if (_isWaitting.exchange(false) == true) {
        std::lock_guard<std::mutex> lock{_eventMutex};
        _event.notify_one();
        return true;
    }
    return false;
}

void LoopRunnable::reqStop(bool reqBreakWait) {
    _isReqStop.exchange(true);
    if (reqBreakWait) {
        breakWait();
    }
}

LoopRunnable& LoopRunnable::reset() {
    _isReqStop.exchange(false);
    _isRunning.exchange(false);
    _isWaitting.exchange(false);
    _loop.exchange(0);
    _startTime = 0;
    return *this;
}

bool LoopRunnable::isRunning() const { return _isRunning.load(); }

bool LoopRunnable::isWaiting() const { return _isWaitting.load(); }

size_t LoopRunnable::getNLoop() const { return _loop.load(); }

std::string LoopRunnable::getName() const { return _name; }

time_t LoopRunnable::getStartTime() const { return _startTime; }
