/*
 * Author: tuantq3
 * File: FixedSizeBlock.h
 *
 * Created on 19/4/2020
 */
#ifndef FIXEDSIZEBLOCK_H
#define FIXEDSIZEBLOCK_H

template <class Arena>
class FixedBlockMemManager {
public:
    // default constructor
    // char (&a)[N] means: "reference to array (length N) of char"
    template <int N>
    FixedBlockMemManager(char (&a)[N]);
    // copy constructor is prohibited
    FixedBlockMemManager(const FixedBlockMemManager& source) = delete;
    // assignment operator is prohibited (copy version)
    FixedBlockMemManager& operator=(const FixedBlockMemManager& source) = delete;
    // default destructor
    ~FixedBlockMemManager() = default;
};
#endif  // FIXEDSIZEBLOCK_H
