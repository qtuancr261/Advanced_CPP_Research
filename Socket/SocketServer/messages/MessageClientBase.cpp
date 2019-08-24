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
    // frameSize: 4 bytes
    if (!buf.writeInt(frameSize)) return false;
    // msgType: 1 byte
    if (!buf.writeInt(msgType)) return false;
    // seqId: 8 bytes
    if (!buf.writeInt(seqId)) return false;
    // Remaining bytes
    return _serializeSpecHeader(buf);
}

bool MessageClientBase::_deserializeCommonHeader(BufferWrapper &buf) {
    // frameSize: 4 bytes
    if (!buf.readInt(frameSize)) return false;
    // msgType: 1 byte
    if (!buf.readInt(msgType)) return false;
    // seqId: 8 bytes
    if (!buf.readInt(seqId)) return false;
    // Remaining bytes
    return _deserializeSpecHeader(buf);
}
