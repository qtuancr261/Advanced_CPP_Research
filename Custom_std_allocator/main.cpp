#include <assert.h>
#include <iostream>
#include <set>
#include "minimalalloc.h"
#include "minimalpoolallocator.h"
#include "poolallocator.h"
using std::cout;
using std::endl;
using std::set;
using EventSentHolder = set<long, std::less<long>, pool_allocator<long>>;
using EventSentHolder_mini = set<long, std::less<long>, mini_allocator<long>>;
using EventSentHolder_mini_pool = set<long, std::less<long>, mini_pool_allocator<long>>;
int main() {
    EventSentHolder _eventSent;
    _eventSent.insert(10);
    _eventSent.insert(20);
    cout << "size of char : " << sizeof(char) << endl;
    mini_allocator<uint64_t> a;
    mini_allocator<int> b;
    assert(a != b);

    mini_allocator<int> c;
    assert(a != c && b == c);

    EventSentHolder_mini_pool _eventSent2;
    _eventSent2.insert(100);
    _eventSent2.insert(200);
    _eventSent2.insert(300);
    return 0;
}
