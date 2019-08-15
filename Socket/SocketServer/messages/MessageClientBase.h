/*
 * Author: tuantq3
 * File: messageclientbase.h
 *
 * Created on 13/8/2019
 */
#ifndef MESSAGECLIENTBASE_H
#define MESSAGECLIENTBASE_H

#include <atomic>
#include <memory>
#include "MessageDef.h"
#include "bufferwrapper.h"

using std::atomic;
class MessageClientBase {
private:
    static inline atomic<int64_t> currentSeqId{0};

public:
    // common headers only
    FrameSize frameSize;
    MessageType msgType;
    SeqId seqId;

public:
    explicit MessageClientBase(MsgType msgType);
    virtual ~MessageClientBase();

protected:
    bool _serializeCommonHeader(BufferWrapper& buf);
    bool _deserializeCommonHeader(BufferWrapper& buf);

    virtual bool _serializeSpecHeader(BufferWrapper& buf) = 0;
    virtual bool _deserializeSpecHeader(BufferWrapper& buf) = 0;
};

#endif  // MESSAGECLIENTBASE_H
