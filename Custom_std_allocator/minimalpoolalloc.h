#ifndef MINIMALPOOLALLOC_H
#define MINIMALPOOLALLOC_H
#include <iostream>
template <typename T>
struct pool_tallocator {
    using value_type = T;
    pool_tallocator() = default;

    template <class U>
    pool_tallocator(const pool_tallocator<U>&) {}
    T* allocate(size_t n, void const* = 0)
    {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* ptr, size_t)
    {
        ::operator delete(ptr);
    }
};
#endif // MINIMALPOOLALLOC_H
