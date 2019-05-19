#ifndef BASICCIRCULARBUFFER_H
#define BASICCIRCULARBUFFER_H
#include <cassert>
#include <cstdlib>
template <typename T>
struct Node {
    T data;
    T* pNext;
};
template <typename T>
class CircularBuffer {
public:
    typedef Node<T>* ptrNodeT;

private:
    ptrNodeT _pHead;
    ptrNodeT _pTail;
    size_t _size;
    size_t _capacity;

public:
    CircularBuffer(size_t maxCapacity) : _pHead{nullptr}, _pTail{nullptr}, _size{0}, _capacity{maxCapacity} { assert(maxCapacity >= 0); }
    ~CircularBuffer() {
        // Implement later
    }

    /// Current size of the circular buffer
    size_t size() const { return _size; }

    /// Max capacity
    size_t capacity() const { return _capacity; }

    ptrNodeT getHead() const { return _pHead; }
    ptrNodeT getTail() const { return _pTail; }

    // FIFO mechanism is well suited
};
#endif  // BASICCIRCULARBUFFER_H
