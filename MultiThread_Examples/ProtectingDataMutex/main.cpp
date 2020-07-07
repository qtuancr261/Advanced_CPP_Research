/*
 * Author: tuantq3
 * File: %{Cpp:License:FileName}
 *
 * Created on 8/9/2019
 */
#include <algorithm>
#include <iostream>
#include <mutex>
#include <vector>
#include "ThreadSafeStack.h"
#include "benchtest/LazyInitBench.h"
#include "hierarchical_mutex.h"
#include "logictest/LogicThreadSafeStack.h"
#include "logictest/logichierarchymutex.h"
#include <gnu/libc-version.h>
using std::lock_guard;
using std::mutex;
using std::vector;

using namespace std;
class GuardVec {
private:
    vector<int> _data;
    mutex _dataMutex;

public:
    GuardVec() = default;
    ~GuardVec() = default;
    void addNewValue(int newValue) {
        lock_guard<mutex> wLock{_dataMutex};
        _data.push_back(newValue);
    }

    bool isValueValid(int lookupValue) {
        lock_guard<mutex> rLock{_dataMutex};
        return (std::find(std::begin(_data), std::end(_data), lookupValue) != std::end(_data));
    }
};

thread_local uint32_t hierarchical_mutex::_thisThreadHierarchyValue{std::numeric_limits<uint32_t>::max()};

int main() {
    cout << "Hello World!" << endl;

    // testStack.pop(popValue);
    LogicTestThreadSafeStack<int>::testPush(1, 300000);
    ThreadSafeStack<int> t1;
    ThreadSafeStack<int> t2;
    t1.swapV1(t2);
    // test hierarchy mutex with two thread
    LogicHierarchyMutex::runHtoLThreadHierarchy();
    LogicHierarchyMutex::runLtoHThreadHierarchy();
    // Benchmark
    // LazyInitBench::benchmarkCallAPI(2, 80000000);

    std::mutex mutexA;

    std::lock_guard<std::mutex> guard1{mutexA};
    cout << "Ending guard 1" << endl;
    guard1.~lock_guard();
    std::lock_guard<std::mutex> guard2{mutexA};
    // Ok we have deadlock situation here
    // Same thread lock an already locked mutex
    cout << "Ending guard 2" << endl;
    cout << "Ending" << endl;

    uint32_t A{100};
    uint64_t B{200000000};
    uint64_t C = A + B;
    cout << C << endl;
    cout << "gnu c version: "<<gnu_get_libc_version() << endl;
    return 0;
}
