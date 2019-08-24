/*
 * Author: tuantq3
 * File: bufferwrapper.h
 *
 * Created on 6/8/2019
 */
#ifndef BUFFERWRAPPER_H
#define BUFFERWRAPPER_H

#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <random>
#include <string>

#define POWEROF2(nbits) (1ull << (nbits))
#define MASK1(nbits) (POWEROF2(nbits) - 1)
using std::cout;

using std::clog;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::seed_seq;
using std::string;
using std::uniform_int_distribution;
// This class doesn't have the ownership with the data it hold
class BufferWrapper {
private:
    uint8_t* _data;
    size_t _sizeRemain;

public:
    BufferWrapper(uint8_t* srcData, size_t dataLen);
    virtual ~BufferWrapper();
    size_t sizeRemain() const;

public:  // write functions
    template <typename T>
    bool writeInt(T value) {
        if (_sizeRemain < sizeof(value)) return false;
        *((T*)_data) = value;
        _data += sizeof(value);
        _sizeRemain -= sizeof(value);
        return true;
    }

    bool writeString(const string& srcString);

public:  // read functions
    template <typename T>
    bool readInt(T& value) {
        if (_sizeRemain < sizeof(value)) return false;
        value = *((T*)_data);
        _data += sizeof(value);
        _sizeRemain -= sizeof(value);
        return true;
    }

    bool readString(string& desString);

public:  // unit tests
    static bool serializeDeserializeNumber();
    static bool serializeDeserializeString();
};

#endif  // BUFFERWRAPPER_H
