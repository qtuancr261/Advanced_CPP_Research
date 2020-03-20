#include "poolallocator.h"
#include "minimalpoolalloc.h"
#include <iostream>
#include <set>
#include <assert.h>
using std::cout;
using std::endl;
using std::set;
using EventSentHolder = set<long, std::less<long>, pool_allocator<long>>;
using EventSentHolder_mini = set<long , std::less<long>, mini_allocator<long>>;
int main()
{
    EventSentHolder _eventSent;
    _eventSent.insert(10);
    _eventSent.insert(20);
    cout << "size of char : " << sizeof(char) << endl;
    mini_allocator<uint64_t> a;
    mini_allocator<int> b;
    assert(a != b);

    mini_allocator<int> c;
    assert(a != c && b == c);
    return 0;
}
