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
    MessageClientReqRegister(MsgType msgType = MsgType::REQ_REGISTER);
    virtual ~MessageClientReqRegister() override = default;

    // MessageClientBase interface
public:
    //
    virtual shared_ptr<uint8_t[]> serialize() override;

protected:
    virtual bool _serializeSpecHeader(BufferWrapper &buf) override;
    virtual bool _deserializeSpecHeader(BufferWrapper &buf) override;

    // MessageClientBase interface
protected:
    virtual size_t calculateFrameSize() const override;
};

#endif  // MESSAGECLIENTREGISTER_H
