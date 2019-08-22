/*
 * Author: tuantq3
 * File: messageclientbase.cpp
 *
 * Created on 13/8/2019
 */
#include "MessageClientBase.h"

MessageClientBase::MessageClientBase(MsgType msgType) : frameSize{}, msgType{static_cast<MessageType>(msgType)}, seqId{++currentSeqId} {}

MessageClientBase::~MessageClientBase() {}

size_t MessageClientBase::calculateFrameSize() const { return sizeof(frameSize) + sizeof(msgType) + sizeof(seqId); }

bool MessageClientBase::_serializeCommonHeader(BufferWrapper &buf) {
    if (buf.writeInt(frameSize)) return false;
    if (buf.writeInt(msgType)) return false;
    if (buf.writeInt(seqId)) return false;
    if (_serializeSpecHeader(buf)) return false;
    return true;
}

bool MessageClientBase::_deserializeCommonHeader(BufferWrapper &buf) {
    if (buf.readInt(frameSize)) return false;
    if (buf.readInt(msgType)) return false;
    if (buf.readInt(seqId)) return false;
    if (_deserializeSpecHeader(buf)) return false;
    return true;
}
