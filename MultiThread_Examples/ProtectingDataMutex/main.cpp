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
#include "hierarchical_mutex.h"
#include "logictest/LogicThreadSafeStack.h"
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
    t1.swap(t2);

    hierarchical_mutex mutex1{10000};
    lock_guard lock1{mutex1};

    return 0;
}
