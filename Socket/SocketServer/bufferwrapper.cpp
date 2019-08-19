/*
 * Author: tuantq3
 * File: bufferwrapper.cpp
 *
 * Created on 6/8/2019
 */
#include "bufferwrapper.h"

BufferWrapper::BufferWrapper(uint8_t *const srcData, size_t dataLen) : _data{srcData}, _sizeRemain{dataLen} {}

BufferWrapper::~BufferWrapper() {}

size_t BufferWrapper::sizeRemain() const { return _sizeRemain; }

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

bool BufferWrapper::writeString(const string &srcString) { return true; }

bool BufferWrapper::readI8(int8_t &value) {
    if (_sizeRemain < sizeof(value)) return false;
    value = (*(int8_t *)_data);
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::readI16(int16_t &value) {
    if (_sizeRemain < sizeof(value)) return false;
    value = (*(int16_t *)_data);
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::readI32(int32_t &value) {
    if (_sizeRemain < sizeof(value)) return false;
    value = (*(int32_t *)_data);
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::readI64(int64_t &value) {
    if (_sizeRemain < sizeof(value)) return false;
    value = (*(int64_t *)_data);
    _data += sizeof(value);
    _sizeRemain -= sizeof(value);
    return true;
}

bool BufferWrapper::readString(string &desString) { return true; }

bool BufferWrapper::serializeDeserializeNumber() {
    const int dataSize = 10;
    uint8_t *data = new uint8_t[dataSize];
    uniform_int_distribution<> udistribution;
    random_device randDev;
    default_random_engine randEngine{randDev()};
    int8_t i8_1 = udistribution(randEngine) & MASK1(8);
    int8_t i8_2 = udistribution(randEngine) & MASK1(8);
    int16_t i16_1 = udistribution(randEngine) & MASK1(16);
    int16_t i16_2 = udistribution(randEngine) & MASK1(16);
    int32_t i32 = udistribution(randEngine) & MASK1(32);
    cout << endl << "i8_1: " << (int)i8_1 << " |i8_2: " << (int)i8_2 << " |i16_1: " << i16_1 << " |i16_2: " << i16_2 << " |i32: " << i32 << endl;
    // Serialize
    BufferWrapper buf{data, dataSize};
    assert(buf.writeI32(i32));
    assert(buf.writeI16(i16_1));
    assert(buf.writeI16(i16_2));
    assert(buf.writeI8(i8_1));
    assert(buf.writeI8(i8_2));
    assert(buf.sizeRemain() == 0);
    // Desialize
    BufferWrapper bufD{data, dataSize};
    int32_t ri32{};
    assert(bufD.readI32(ri32));
    assert(ri32 == i32);
    int16_t ri16_1{};
    assert(bufD.readI16(ri16_1));
    assert(ri16_1 == i16_1);
    int16_t ri16_2{};
    assert(bufD.readI16(ri16_2));
    assert(ri16_2 == i16_2);
    int8_t ri8_1{};
    assert(bufD.readI8(ri8_1));
    assert(ri8_1 == i8_1);
    int8_t ri8_2{};
    assert(bufD.readI8(ri8_2));
    assert(ri8_2 == i8_2);
    assert(bufD.sizeRemain() == 0);
    std::cout << "Passed test Serialize - Deserizalize number" << std::endl;
    delete[] data;
    return true;
}
