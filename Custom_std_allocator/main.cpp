#include "poolallocator.h"
#include "minimalpoolalloc.h"
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;
using EventSentHolder = set<long, std::less<long>, pool_allocator<long>>;
using EventSentHolder_mini = set<long , std::less<long>, pool_tallocator<long>>;
int main()
{
    EventSentHolder _eventSent;
    EventSentHolder_mini _eventSent_mini;
    return 0;
}
