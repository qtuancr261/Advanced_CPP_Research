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

shared_ptr<uint8_t[]> MessageClientReqRegister::serialize() {
    frameSize = static_cast<FrameSize>(calculateFrameSize());
    shared_ptr<uint8_t[]> serializedData{new uint8_t[frameSize]};
    // Make sure bvffer Wrapper doesn't take ownership of the serialized data
    BufferWrapper serializedDataWrapper{serializedData.get(), static_cast<size_t>(frameSize)};
    if (_serializeCommonHeader(serializedDataWrapper))
        return serializedData;
    else {
        return nullptr;
    }
}

bool MessageClientReqRegister::_serializeSpecHeader(BufferWrapper &buf) { return true; }

bool MessageClientReqRegister::_deserializeSpecHeader(BufferWrapper &buf) { return true; }

size_t MessageClientReqRegister::calculateFrameSize() const {
    return MessageClientBase::calculateFrameSize() + sizeof(uint32_t) /* 4 bytes size */ + name.size();
}
