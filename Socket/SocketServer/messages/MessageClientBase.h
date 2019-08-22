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
using std::make_shared;
using std::shared_ptr;
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
    // Use this method for serialize - deserialize
    // Before C++17, only std::unique_ptr was able to handle arrays out of the box
    // Now it's also possible with std::shared_ptr except std::make_shared (until C++20)
    virtual shared_ptr<uint8_t[]> serialize() = 0;

protected:
    virtual size_t calculateFrameSize() const;
    bool _serializeCommonHeader(BufferWrapper& buf);
    bool _deserializeCommonHeader(BufferWrapper& buf);

    virtual bool _serializeSpecHeader(BufferWrapper& buf) = 0;
    virtual bool _deserializeSpecHeader(BufferWrapper& buf) = 0;
};

#endif  // MESSAGECLIENTBASE_H
