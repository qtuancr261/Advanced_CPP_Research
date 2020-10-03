/*
 * Author: tuantq3
 * File: ThreadSafeQueue.h
 *
 * Created on 7/7/2020
 */
#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
template <typename T>
class ThreadSafeQueue {
    mutable std::mutex _mutex;
    std::queue<T> _data;
    std::condition_variable _condition;

public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue& srcQueue) {
        std::lock_guard<std::mutex> lock{srcQueue._mutex};
        _data = srcQueue._data;
    }
    ThreadSafeQueue& operator=(const ThreadSafeQueue& srcQueue) = delete;
    ~ThreadSafeQueue() = default;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock{_mutex};
        _data.push(value);
        _condition.notify_one();
        // noti any thread is waiting for data
    }

    // wait operations
    void waitAndPop(T& popValue) {
        std::unique_lock<std::mutex> lock{_mutex};
        _condition.wait(lock, [this]() { return !_data.empty(); });
        // wait till _data is not empty
        popValue = _data.front();
        _data.pop();
    }
    std::shared_ptr<T> waitAndPop() {
        std::unique_lock<std::mutex> lock{_mutex};
        _condition.wait(lock, [this]() { return !_data.empty(); });
        std::shared_ptr<T> popValue{std::make_shared(_data.front())};
        _data.pop();
        return popValue;
    }

    // try operations
    void tryAndPop(T& popValue) {
        std::lock_guard<std::mutex> lock{_mutex};
        if (!_data.empty()) {
            popValue = _data.front();
            _data.pop();
        }
    }
    std::shared_ptr<T> tryAndPop() {
        std::lock_guard<std::mutex> lock{_mutex};
        std::shared_ptr<T> popValue{};
        if (!_data.empty()) {
            popValue = std::make_shared<T>(_data.front());
            _data.pop();
        }
        return popValue;
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> lock{_mutex};
        return _data.empty();
    }
};
#endif  // THREADSAFEQUEUE_H
