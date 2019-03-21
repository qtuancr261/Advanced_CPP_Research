#include "poolallocator.h"
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;
using EventSentHolder = set<long, std::less<long>, pool_allocator<long>>;
int main()
{
    EventSentHolder _eventSent;
    for (int var = 0; var < 1000000; ++var) {
        _eventSent.insert(var);
    }
    return 0;
}
