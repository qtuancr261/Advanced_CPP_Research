/*
 * Author: tuantq3
 * File: bufferwrapper.cpp
 *
 * Created on 6/8/2019
 */
#include "bufferwrapper.h"

BufferWrapper::BufferWrapper(uint8_t *const srcData, size_t dataLen) : _data{srcData}, _sizeRemain{dataLen} {}

BufferWrapper::~BufferWrapper() {}

bool BufferWrapper::writeI8(int8_t value) {
    if (_sizeRemain < sizeof(value)) return false;
    *((int8_t *)_data) = value;
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::writeI16(int16_t value) {
    if (_sizeRemain < sizeof(value)) return false;
    *((int16_t *)_data) = value;
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::writeI32(int32_t value) {
    if (_sizeRemain < sizeof(value)) return false;
    (*(int32_t *)_data) = value;
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::writeI64(int64_t value) {
    if (_sizeRemain < sizeof(value)) return false;
    (*(int64_t *)_data) = value;
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::readI8(int8_t &value) {}

bool BufferWrapper::readI16(int16_t &value) {}

bool BufferWrapper::readI32(int32_t &value) {}

bool BufferWrapper::readI64(int64_t &value) {}
