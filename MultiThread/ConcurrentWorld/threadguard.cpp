#include "threadguard.h"

ThreadGuard::ThreadGuard(std::thread &srcThread) : _guardThread{srcThread} {}

ThreadGuard::~ThreadGuard() {
    if (_guardThread.joinable()) {
        _guardThread.join();
    }
}
