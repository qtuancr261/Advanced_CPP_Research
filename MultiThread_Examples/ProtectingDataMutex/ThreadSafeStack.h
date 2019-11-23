/*
 * Author: tuantq3
 * File: ThreadSafeStack.h
 *
 * Created on 15/10/2019
 */
#ifndef THREADSAFESTACK_H
#define THREADSAFESTACK_H

#include <exception>
#include <limits>
#include <memory>
#include <mutex>
#include <stack>
using std::make_shared;
using std::shared_ptr;
class stack_empty : public std::exception {
private:
    static inline std::string message{"Stack empty"};

public:
    stack_empty() = default;
    const char* what() const noexcept { return message.c_str(); }
    ~stack_empty() = default;
};

template <typename T>
class ThreadSafeStack {
private:
    std::stack<T> _data;
    std::mutex _dataMutex;

public:
    ThreadSafeStack() = default;
    ThreadSafeStack(const ThreadSafeStack& source) {
        std::lock_guard<std::mutex> lockData{source._dataMutex};
        _data = source._data;
    }
    ThreadSafeStack& operator=(const ThreadSafeStack& source) = delete;
    ~ThreadSafeStack() = default;

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
        if (_data.empty()) throw stack_empty();
        poppedValue = _data.top();
        _data.pop();
    }

    shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lockData{_dataMutex};
        if (_data.empty()) throw stack_empty();
        shared_ptr<T> topValue{make_shared<T>(_data.top())};
        _data.pop();
        return topValue;
    }

    size_t size() {
        std::lock_guard<std::mutex> lockData{_dataMutex};
        return _data.size();
    }

    void swap(ThreadSafeStack& other) {
        if (this == &other) return;
        // std::lock function can lock two or more mutexes at one without risk of deadlock
        std::lock(this->_dataMutex, other._dataMutex);
        // we use std::adopt_lock to indicate to the std::lock_guard object
        // that the mutexes are already lock and they should kust adopt the ownership
        // of the existing lock on the mutex rather than attempt to lock it again
        std::lock_guard<std::mutex> lock1(this->_dataMutex, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(other._dataMutex, std::adopt_lock);
        std::swap(this->_data, other._data);
    }
};
#endif  // THREADSAFESTACK_H
