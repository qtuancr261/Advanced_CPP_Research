/*
 * Author: tuantq3
 * File: ThreadSafeStack.h
 *
 * Created on 15/10/2019
 */
#ifndef THREADSAFESTACK_H
#define THREADSAFESTACK_H

#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>
template <typename T>
class ThreadSafeStack {
private:
    std::stack<T> _data;
    std::mutex _dataMutex;
    ThreadSafeStack() = default;
    ThreadSafeStack(const ThreadSafeStack& source) {
        std::lock_guard<std::mutex> lockData{source._dataMutex};
        _data = source._data;
    }
    ThreadSafeStack& operator=(const ThreadSafeStack& source) = delete;
    ~ThreadSafeStack() = delete;

    bool isEmpty() const {
        std::lock_guard<std::mutex> lockData{_dataMutex};
        return _data.empty();
    }

    void push(const T& value) {
        std::lock_guard<std::mutex> lockData{_dataMutex};
        _data.push(value);
    }

    void pop(T& poppedValue) {
        std::lock_guard<std::mutex> lockData{_dataMutex};
        if (_data.empty()) throw std::exception();
        poppedValue = _data.top();
        _data.pop();
    }
};
#endif  // THREADSAFESTACK_H
