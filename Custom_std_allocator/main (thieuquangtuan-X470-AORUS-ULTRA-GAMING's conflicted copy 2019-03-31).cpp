#include "minimalpoolalloc.h"
#include "poolallocator.h"
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;
using EventSentHolder = set<long, std::less<long>, pool_allocator<long>>;
using EventSentHolder_m = set<long, std::less<long>, pool_tallocator<long>>;
int main()
{
    EventSentHolder _eventSent;
    _eventSent.insert(10);
    _eventSent.insert(20);

    EventSentHolder_m _eventSent_m;
    _eventSent_m.insert(290);
    _eventSent_m.insert(250);
    cout << _eventSent_m.size() << endl;
    return 0;
}
