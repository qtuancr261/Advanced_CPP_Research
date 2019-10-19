/*
 * Author: tuantq3
 * File: LogicThreadSafeStack.h
 *
 * Created on 19/10/2019
 */
#ifndef LOGICTHREADSAFESTACK_H
#define LOGICTHREADSAFESTACK_H
#include <assert.h>
#include <iostream>
#include <thread>
#include <vector>
#include "ThreadSafeStack.h"
#define VERIFY_MULTITHREAD(threads) assert(threads > 1)
using std::thread;
template <typename T>
class LogicTestThreadSafeStack {
private:
    static inline const int MAX_THREADS{static_cast<int>(thread::hardware_concurrency())};
    // push or pop entries at least per thread
    static inline const int MIN_ENTRIES_PER_THREAD{100};

public:
    LogicTestThreadSafeStack() = default;

private:
    static void _pushData(uint64_t min, uint64_t max, ThreadSafeStack<T>& testedObject) {
        for (uint64_t i{min}; i <= max; ++i) {
            // make sure we can cast it to T
            T entry{static_cast<T>(i)};
            testedObject.push(entry);
        }
    }

public:
    static void testPush(uint64_t minRange, uint64_t maxRange, int expectedThreads) {
        VERIFY_MULTITHREAD(expectedThreads);
        // int calThreads = 2;
        uint64_t totalEntries = maxRange - minRange + 1;
        if (totalEntries <= MIN_ENTRIES_PER_THREAD) {
            std::cerr << "Total entries is smaller than minimun entries per thread ";
            return;
        }
        uint64_t entriesPerThread{totalEntries / expectedThreads};
        return;
    }

public:
};
#endif  // LOGICTHREADSAFESTACK_H
