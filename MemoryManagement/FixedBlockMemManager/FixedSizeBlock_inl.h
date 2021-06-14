/*
 * Author: tuantq3
 * File: FixedSizeBlock_inl.h
 * Modern C++ Coding note
 * To keep the template code clean we can keep the member functions def in a file *_inl
 * for "inline definitions". When the member functions appear outside the template class
 * "inline" keyword must be explicitly provided, help the compiler connect the definitions
 * with the declarations in the template class body, as inline linkage is assumed only when
 * the definitions apprears inside the class
 * Created on 20/4/2020
 */
#ifndef FIXEDSIZEBLOCK_INL_H
#define FIXEDSIZEBLOCK_INL_H
#include <exception>
#include "FixedSizeBlock.h"

template <class Arena>
template <int N>
inline FixedBlockMemManager<Arena>::FixedBlockMemManager(char (&a)[N]) : _freeHead{nullptr}, _blockSize{0}, _arena{a} {
    // nothing here :v
}

template <class Arena>
inline void* FixedBlockMemManager<Arena>::allocate(size_t size) {
    if (isEmpty()) {
        _freeHead = reinterpret_cast<freeBlock*>(_arena.allocate(size));
        _blockSize = size;
        if (isEmpty()) throw std::bad_alloc();
    }
    if (_blockSize != size) throw std::bad_alloc();
    auto retPtr = _freeHead;
    _freeHead = _freeHead->nextBlock;
    return retPtr;
}

template <class Arena>
inline void FixedBlockMemManager<Arena>::deallocate(void* ptr) {
    if (ptr == nullptr) return;
    auto retPtr = reinterpret_cast<freeBlock*>(ptr);
    retPtr->nextBlock = _freeHead;
    _freeHead = retPtr;
}

template <class Arena>
inline size_t FixedBlockMemManager<Arena>::capacity() const {
    return _arena.capacity();
}

template <class Arena>
inline size_t FixedBlockMemManager<Arena>::blockSize() const {
    return _blockSize;
}

template <class Arena>
inline void FixedBlockMemManager<Arena>::clear() {
    _freeHead == nullptr;
    _arena.clear();
}

template <class Arena>
inline bool FixedBlockMemManager<Arena>::isEmpty() const {
    return _freeHead == nullptr;
}

#endif  // FIXEDSIZEBLOCK_INL_H
