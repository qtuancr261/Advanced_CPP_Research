#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <iostream>
template <typename T>
class pool_allocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
};
#endif // POOLALLOCATOR_H
