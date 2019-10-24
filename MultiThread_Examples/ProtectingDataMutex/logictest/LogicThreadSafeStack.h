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
    static inline const uint64_t MAX_THREADS{static_cast<uint64_t>(thread::hardware_concurrency())};
    // push or pop entries at least per thread
    static inline const uint64_t MIN_ENTRIES_PER_THREAD{10};

public:
    LogicTestThreadSafeStack() = default;

public:
    static void _pushData(uint64_t min, uint64_t max, ThreadSafeStack<T>& testedObject) {
        std::cout << "push " << min << ":" << max << std::endl;
        for (uint64_t i{min}; i < max; ++i) {
            // make sure we can cast it to T
            T entry{static_cast<T>(i)};
            testedObject.push(entry);
        }
    }

public:
    static void testPush(uint64_t minRange, uint64_t maxRange) {
        // int calThreads = 2;
        uint64_t totalEntries = maxRange - minRange + 1;
        if (totalEntries <= MIN_ENTRIES_PER_THREAD) {
            std::cerr << "Total entries is smaller than minimun entries per thread ";
            return;
        }
        std::cout << "Total entries: " << totalEntries << std::endl;
        ThreadSafeStack<T> testObject;
        uint64_t expectedThreads{totalEntries / MIN_ENTRIES_PER_THREAD};
        uint64_t numThreads{expectedThreads > MAX_THREADS ? MAX_THREADS / 2 : expectedThreads};
        uint64_t entriesPerThread{totalEntries / numThreads};
        std::cout << "Threads: " << numThreads << std::endl;
        std::cout << "Entries per thread: " << entriesPerThread << std::endl;
        std::vector<thread> threads;
        uint64_t midRange{};
        //threads.reserve(numThreads);
        for (int idx{}; idx < numThreads; ++idx) {
            midRange = minRange + entriesPerThread;
	    if (idx == numThreads - 1)
                threads.push_back(thread{&LogicTestThreadSafeStack::_pushData, minRange, maxRange, std::ref(testObject)});
	    else
            	threads.push_back(thread{&LogicTestThreadSafeStack::_pushData, minRange, midRange, std::ref(testObject)});
            minRange += entriesPerThread;
        }
        for (std::thread& threadX : threads) {
            threadX.join();
        }
        std::cout << "Size : " << testObject.size() << std::endl;
        return;
    }

public:
};
#endif  // LOGICTHREADSAFESTACK_H
