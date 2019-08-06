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
#include <cstring>
// This class doesn't have the ownership with the data it hold
class BufferWrapper {
private:
    uint8_t* _data;
    size_t _sizeRemain;

public:
    BufferWrapper(uint8_t* const srcData, size_t dataLen);
    virtual ~BufferWrapper();

public:  // write functions
    bool writeI8(int8_t value);
    bool writeI16(int16_t value);
    bool writeI32(int32_t value);
    bool writeI64(int64_t value);

public:  // read functions
    bool readI8(int8_t& value);
    bool readI16(int16_t& value);
    bool readI32(int32_t& value);
    bool readI64(int64_t& value);
};

#endif  // BUFFERWRAPPER_H
