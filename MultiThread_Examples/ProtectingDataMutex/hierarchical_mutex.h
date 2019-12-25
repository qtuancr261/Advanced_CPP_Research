/*
 * Author: tuantq3
 * File: hierarchical_mutex.h
 *
 * Created on 24/12/2019
 */
#ifndef HIERARCHICAL_MUTEX_H
#define HIERARCHICAL_MUTEX_H

#include <mutex>
using std::lock_guard;
using std::mutex;
// Implement a basic lock hierarchy concept for c++
// The idea is that you devide your app into layers and identify all the mutexs
// that may be locked in any given layer.
// When code tries to lock a mutex, it isn't permitted to lock that mutex
// if it already holds a lock from a lower layer

class hierarchical_mutex {
private:
    mutex _internalMutex;
    uint32_t const _hierarchyValue;
    uint32_t _pre_hierarchyValue;
    static thread_local uint32_t _thisThreadHierarchyValue;

public:
    explicit hierarchical_mutex(uint32_t value);
    void checkHierarchyViolation();
};

#endif  // HIERARCHICAL_MUTEX_H
