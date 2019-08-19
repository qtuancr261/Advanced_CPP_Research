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

bool BufferWrapper::writeString(const string &srcString) { return true; }

bool BufferWrapper::readString(string &desString) { return true; }

bool BufferWrapper::serializeDeserializeNumber() {
    const int dataSize = 10;
    uint8_t *data = new uint8_t[dataSize];
    uniform_int_distribution<> udistribution;
    random_device randDev;
    default_random_engine randEngine{randDev()};
    uint8_t i8_1 = udistribution(randEngine) & MASK1(8);
    uint8_t i8_2 = udistribution(randEngine) & MASK1(8);
    uint16_t i16_1 = udistribution(randEngine) & MASK1(16);
    uint16_t i16_2 = udistribution(randEngine) & MASK1(16);
    uint32_t i32 = udistribution(randEngine) & MASK1(32);
    cout << endl << "i8_1: " << (int)i8_1 << " |i8_2: " << (int)i8_2 << " |i16_1: " << i16_1 << " |i16_2: " << i16_2 << " |i32: " << i32 << endl;
    // Serialize
    BufferWrapper buf{data, dataSize};
    assert(buf.writeInt(i32));
    assert(buf.writeInt(i16_1));
    assert(buf.writeInt(i16_2));
    assert(buf.writeInt(i8_1));
    assert(buf.writeInt(i8_2));
    assert(buf.sizeRemain() == 0);
    // Desialize
    BufferWrapper bufD{data, dataSize};
    uint32_t ri32{};
    assert(bufD.readInt(ri32));
    assert(ri32 == i32);
    uint16_t ri16_1{};
    assert(bufD.readInt(ri16_1));
    assert(ri16_1 == i16_1);
    uint16_t ri16_2{};
    assert(bufD.readInt(ri16_2));
    assert(ri16_2 == i16_2);
    uint8_t ri8_1{};
    assert(bufD.readInt(ri8_1));
    assert(ri8_1 == i8_1);
    uint8_t ri8_2{};
    assert(bufD.readInt(ri8_2));
    assert(ri8_2 == i8_2);
    assert(bufD.sizeRemain() == 0);
    std::cout << "Passed test Serialize - Deserizalize number" << std::endl;
    delete[] data;
    return true;
}
