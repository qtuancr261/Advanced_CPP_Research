/*
 * Author: tuantq3
 * File: messageclientregister.h
 *
 * Created on 13/8/2019
 */
#ifndef MESSAGECLIENTREGISTER_H
#define MESSAGECLIENTREGISTER_H

#include "MessageClientBase.h"
class MessageClientReqRegister : public MessageClientBase {
public:
    string name;
    explicit MessageClientReqRegister(MsgType msgType = MsgType::REQ_REGISTER);
    virtual ~MessageClientReqRegister() override = default;

    bool operator==(const MessageClientReqRegister& srcMessage) const;

    // MessageClientBase interface
public:
    //
    virtual bool serialize(shared_ptr<uint8_t[]>& data, size_t& dataSize) override;
    virtual bool deserialize(shared_ptr<uint8_t[]>& data, size_t& dataSize) override;
    static bool testSerializeDeserialize();

protected:
    virtual bool _serializeSpecHeader(BufferWrapper& buf) override;
    virtual bool _deserializeSpecHeader(BufferWrapper& buf) override;

    // MessageClientBase interface
protected:
    virtual size_t calculateFrameSize() const override;
};

#endif  // MESSAGECLIENTREGISTER_H
