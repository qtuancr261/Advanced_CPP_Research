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
    _eventSent.insert(1);
    _eventSent.insert(2);
    return 0;
}
