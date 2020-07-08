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
    std::mutex _mutex;
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
    }
};
#endif  // THREADSAFEQUEUE_H
