/*
 * Author: tuantq3
 * File: messageclientregister.cpp
 *
 * Created on 13/8/2019
 */
#include "MessageClientReqRegister.h"

MessageClientReqRegister::MessageClientReqRegister(MsgType msgType) : MessageClientBase{msgType}, name{} {
    // default constructor
}

bool MessageClientReqRegister::serialize(shared_ptr<uint8_t[]> &data, size_t &dataSize) {
    dataSize = calculateFrameSize();
    shared_ptr<uint8_t[]> tempData{new uint8_t[dataSize]};
    data.swap(tempData);
    // Correct frameSize header
    frameSize = dataSize;
    // Make sure buffer Wrapper doesn't take ownership of the serialized data
    BufferWrapper serializedDataWrapper{data.get(), dataSize};
    return _serializeCommonHeader(serializedDataWrapper);
}

bool MessageClientReqRegister::deserialize(shared_ptr<uint8_t[]> &data, size_t &dataSize) {}
bool MessageClientReqRegister::_serializeSpecHeader(BufferWrapper &buf) { return true; }

bool MessageClientReqRegister::_deserializeSpecHeader(BufferWrapper &buf) { return true; }

size_t MessageClientReqRegister::calculateFrameSize() const {
    return MessageClientBase::calculateFrameSize() + sizeof(uint32_t) /* 4 bytes size */ + name.size();
}
