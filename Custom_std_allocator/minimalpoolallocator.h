/*
 * Author: tuantq3
 * File: minimalpoolallocator.h
 *
 * Created on 20/3/2020
 */
#ifndef MINIMALPOOLALLOCATOR_H
#define MINIMALPOOLALLOCATOR_H
#include <cstdlib>
#include <forward_list>
#include <stdexcept>
#include <type_traits>
#include <vector>
#define N_SLOT 10000
template <typename T>
class mini_pool_allocator {
private:
    std::vector<T*> _chunksBase;
    std::forward_list<T*> _nodesFree;

public:
    using value_type = T;
    mini_pool_allocator() = default;
    ~mini_pool_allocator() {
        printf("mini_pool_allocator free %d chunks \n", _chunksBase.size());
        while (!_chunksBase.empty()) {
            ::operator delete[](_chunksBase.back());
            _chunksBase.pop_back();
        }
    }

    template <class U>
    mini_pool_allocator(const mini_pool_allocator<U>&) {}
    T* allocate(size_t n, void const* = 0) {
        if (n > 1) throw std::invalid_argument("mimi pool allocator doesn't support allocate n > 1 per called");
        if (_nodesFree.empty()) {
            // create new chunk;
            T* newchunk{(T*)::operator new(N_SLOT * sizeof(T))};
            _chunksBase.push_back(newchunk);
            // arrange N_SLOT nodes to _nodeFree
            for (int i{}; i < N_SLOT; ++i) {
                _nodesFree.push_front(newchunk + i);
            }
        }
        // return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
        T* allocNode = _nodesFree.front();
        _nodesFree.pop_front();
        printf("mini_pool_allocator freeNodes %d \n", std::distance(_nodesFree.begin(), _nodesFree.end()));
        return allocNode;
    }
    void deallocate(T* ptr, size_t n) {
        if (n > 1) throw std::invalid_argument("mimi pool allocator doesn't support deallocate n > 1 per called");
        _nodesFree.push_front(ptr);
        //::operator delete(ptr);
    }
};

template <typename T, typename U>
inline bool operator==(const mini_pool_allocator<T>&, const mini_pool_allocator<U>&) {
    return std::is_same<T, U>::value;
}

template <typename T, typename U>
inline bool operator!=(const mini_pool_allocator<T>& a, const mini_pool_allocator<U>& b) {
    return !(a == b);
}

#endif  // MINIMALPOOLALLOCATOR_H
