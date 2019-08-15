/*
 * Author: tuantq3
 * File: messageclientbase.cpp
 *
 * Created on 13/8/2019
 */
#include "MessageClientBase.h"

MessageClientBase::MessageClientBase(MsgType msgType) : frameSize{}, msgType{static_cast<MessageType>(msgType)}, seqId{++currentSeqId} {}

MessageClientBase::~MessageClientBase() {}

bool MessageClientBase::_serializeCommonHeader(BufferWrapper &buf) {
    if (buf.writeI32(frameSize)) return false;
    if (buf.writeI8(msgType)) return false;
    if (buf.writeI64(seqId)) return false;
    if (_serializeSpecHeader(buf)) return false;
    return true;
}

bool MessageClientBase::_deserializeCommonHeader(BufferWrapper &buf) {
    if (buf.readI32(frameSize)) return false;
    if (buf.readI8(msgType)) return false;
    if (buf.readI64(seqId)) return false;
    if (_deserializeSpecHeader(buf)) return false;
    return true;
}
