/*
 * Author: tuantq3
 * File: messageclientbase.h
 *
 * Created on 13/8/2019
 */
#ifndef MESSAGECLIENTBASE_H
#define MESSAGECLIENTBASE_H

#include <atomic>
#include "MessageDef.h"

using std::atomic;
class MessageClientBase {
private:
    static inline atomic<int64_t> currentSeqId{0};

public:
    // common headers only
    FrameSize frameSize;
    MessageType msgType;
    ProtocolVersion version;
    SeqId seqId;

public:
    explicit MessageClientBase(MsgType msgType);
    virtual ~MessageClientBase();

protected:
    bool _serializeCommonHeader();
    bool _deserializeCommonHeader();
};

#endif  // MESSAGECLIENTBASE_H
