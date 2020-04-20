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
#include "FixedSizeBlock.h"

template <class Arena>
template <int N>
inline FixedBlockMemManager<Arena>::FixedBlockMemManager(char (&a)[N]) : _freeHead{nullptr}, _blockSize{0}, _arena{a} {
    // nothing here :v
}
#endif  // FIXEDSIZEBLOCK_INL_H
