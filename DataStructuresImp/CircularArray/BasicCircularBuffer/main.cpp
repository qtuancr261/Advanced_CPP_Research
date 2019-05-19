#include <iostream>
#include "basiccircularbuffer.h"
using namespace std;

int main() {
    CircularBuffer<int> eventHolder(5);
    cout << "EventHolder size: " << eventHolder.size() << endl;
    return 0;
}
