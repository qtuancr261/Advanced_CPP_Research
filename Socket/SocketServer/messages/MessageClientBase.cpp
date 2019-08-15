/*
 * Author: tuantq3
 * File: messageclientbase.cpp
 *
 * Created on 13/8/2019
 */
#include "MessageClientBase.h"

MessageClientBase::MessageClientBase(MsgType msgType) : frameSize{}, msgType{static_cast<MessageType>(msgType)}, seqId{++currentSeqId} {}

MessageClientBase::~MessageClientBase() {}

bool MessageClientBase::_serializeCommonHeader(BufferWrapper &buf) { return true; }

bool MessageClientBase::_deserializeCommonHeader(BufferWrapper &buf) { return true; }
