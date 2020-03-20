#ifndef MINIMALPOOLALLOC_H
#define MINIMALPOOLALLOC_H
#include <iostream>
template <typename T>
struct mini_allocator {
    using value_type = T;
    mini_allocator() = default;

    template <class U>
    mini_allocator(const mini_allocator<U>&) {}
    T* allocate(size_t n, void const* = 0)
    {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* ptr, size_t)
    {
        ::operator delete(ptr);
    }
};

template <typename T, typename U>
inline bool operator ==(const mini_allocator<T>&, const mini_allocator<U>&) {
    return std::is_same<T, U>::value;
}

template <typename T, typename U>
inline bool operator !=(const mini_allocator<T>& a, const mini_allocator<U>& b) {
    return !(a == b);
}

#endif // MINIMALPOOLALLOC_H
