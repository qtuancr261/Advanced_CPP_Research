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

int main() {
    cout << "Hello World!" << endl;
    ThreadSafeStack<int> testStack;
    int popValue = 0;
    testStack.pop(popValue);
    return 0;
}
