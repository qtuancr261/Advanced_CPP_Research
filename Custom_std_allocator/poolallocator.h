#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H
#include <deque>
#include <iostream>
#define N_SLOT 10000
template <typename T>
struct element {
    element* ptrNext;
    T data;
    element()
        : ptrNext{ nullptr }
        , data{}
    {
    }
};
template <typename T>
class pool_allocator {
private:
    element<T>* _freeHead;
    element<T>* _freeTail;
    std::deque<element<T>*> _base;

public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    template <typename T1>
    struct rebind {
        typedef pool_allocator<T1> other;
    };

#if __cplusplus >= 201103L
    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 2103. propagate_on_container_move_assignment
    typedef std::true_type propagate_on_container_move_assignment;
#endif

    pool_allocator()
        : _freeHead{ nullptr }
        , _freeTail{ nullptr }
    {
        // Create the first chunk
        element<T>* newChunk = (element<T>*)malloc(N_SLOT * sizeof(element<T>));
        std::cout << " size eleT " << sizeof(element<T>) << "size T " << sizeof(T) << std::endl;
        _base.push_back(newChunk);
        _freeHead = newChunk;
        _freeHead->ptrNext = _freeHead + 1;
        element<T>* currentElement = _freeHead->ptrNext;
        for (int var = 1; var < N_SLOT - 1; ++var) {
            currentElement->ptrNext = currentElement + 1;
            currentElement = currentElement->ptrNext;
        }
        // the last element
        currentElement->ptrNext = nullptr;
        _freeTail = currentElement;
    }

    pool_allocator(const pool_allocator&)
        : _freeHead{ nullptr }
        , _freeTail{ nullptr }
    {
    }

    template <typename T1>
    pool_allocator(const pool_allocator<T1>&) {}

    ~pool_allocator()
    {
        std::cout << "Release all " << _base.size() << std::endl;
        element<T>* chunk;
        while (!_base.empty()) {
            chunk = _base.front();
            if (chunk != NULL) {
                free(chunk);
                _base.pop_front();
            }
        }
    }

    pointer address(reference __x) const { return std::__addressof(__x); }

    const_pointer address(const_reference __x) const
    {
        return std::__addressof(__x);
    }

    // NB: __n is permitted to be 0.  The C++ standard says nothing
    // about what the return value is when __n == 0.

    pointer allocate(size_type __n, const void* = 0)
    {
        std::cout << "alloc with n " << __n << std::endl;
        if (__n > this->max_size())
            std::__throw_bad_alloc();
        // return static_cast<T*> (::operator new(__n * sizeof (T)));
        // create new chunk
        if (_freeHead == nullptr && _freeTail == nullptr)
        {
            element<T>* newChunk = (element<T>*)malloc(N_SLOT * sizeof(element<T>));
            std::cout << " size eleT " << sizeof(element<T>) << "size T " << sizeof(T) << std::endl;
            _base.push_back(newChunk);
            _freeHead = newChunk;
            _freeHead->ptrNext = _freeHead + 1;
            element<T>* currentElement = _freeHead->ptrNext;
            for (int var = 1; var < N_SLOT - 1; ++var) {
                currentElement->ptrNext = currentElement + 1;
                currentElement = currentElement->ptrNext;
            }
            // the last element
            currentElement->ptrNext = nullptr;
            _freeTail = currentElement;
        }
        // unlink free
        element<T>* allocElement = _freeHead;
        _freeHead = _freeHead->ptrNext;
        allocElement->ptrNext = nullptr;
        if (_freeHead == nullptr) {
            _freeTail = nullptr;
        }
        size_t dataAddr = reinterpret_cast<size_t>(allocElement) + 8;
        // return static_cast<T*> (dataAddr);
        return (T*)(dataAddr);
    }

    // __p is not permitted to be a null pointer.

    void deallocate(pointer __p, size_type)
    {
        std::cout << "dealloc" << std::endl;
        //::operator delete(__p);
        size_t dataAddr = reinterpret_cast<size_t>(__p) - 8;
        element<T>* deallocElement = (element<T>*)(dataAddr);

        if (_freeHead == nullptr && _freeTail == nullptr) {
            _freeHead = _freeTail = deallocElement;
            _freeHead->ptrNext = nullptr;
        }

        // link free
        _freeTail->ptrNext = deallocElement;
        _freeTail = deallocElement;
        _freeTail->ptrNext = nullptr;
    }

    size_type max_size() const { return size_t(-1) / sizeof(T); }

    void construct(pointer __p, const T& __val)
    {
        ::new ((void*)__p) T(__val);
    }

    void destroy(pointer __p) { __p->~T(); }
};
#endif // POOLALLOCATOR_H
