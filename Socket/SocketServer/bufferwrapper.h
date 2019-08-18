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
using std::default_random_engine;
using std::random_device;
using std::seed_seq;
using std::string;
// This class doesn't have the ownership with the data it hold
class BufferWrapper {
private:
    uint8_t* _data;
    size_t _sizeRemain;

public:
    BufferWrapper(uint8_t* const srcData, size_t dataLen);
    virtual ~BufferWrapper();
    size_t sizeRemain() const;

public:  // write functions
    bool writeI8(int8_t value);
    bool writeI16(int16_t value);
    bool writeI32(int32_t value);
    bool writeI64(int64_t value);
    bool writeString(const string& srcString);

public:  // read functions
    bool readI8(int8_t& value);
    bool readI16(int16_t& value);
    bool readI32(int32_t& value);
    bool readI64(int64_t& value);
    bool readString(string& desString);

public:  // unit tests
    static bool serializeDeserializeNumber();
};

#endif  // BUFFERWRAPPER_H
