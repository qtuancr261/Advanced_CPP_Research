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

bool MessageClientReqRegister::operator==(const MessageClientReqRegister &srcMessage) const {
    clog << frameSize << " - " << srcMessage.frameSize << endl;
    if (frameSize != srcMessage.frameSize) return false;
    clog << msgType << " - " << srcMessage.msgType << endl;
    if (msgType != srcMessage.msgType) return false;
    clog << seqId << " - " << srcMessage.seqId << endl;
    if (seqId != srcMessage.seqId) return false;
    clog << name << " - " << srcMessage.name << endl;
    if (name != srcMessage.name) return false;
    return true;
}

bool MessageClientReqRegister::serialize(shared_ptr<uint8_t[]> &data, size_t &dataSize) {
    dataSize = calculateFrameSize();
    shared_ptr<uint8_t[]> tempData{new uint8_t[dataSize]};
    data.swap(tempData);
    // Correct frameSize header
    frameSize = static_cast<FrameSize>(dataSize);
    // Make sure buffer Wrapper doesn't take ownership of the serialized data
    BufferWrapper serializedDataWrapper{data.get(), dataSize};
    return _serializeCommonHeader(serializedDataWrapper);
}

bool MessageClientReqRegister::deserialize(shared_ptr<uint8_t[]> &data, size_t &dataSize) {
    if (data.get() == nullptr) return false;
    BufferWrapper deserializeDataWrapper{data.get(), dataSize};
    return _deserializeCommonHeader(deserializeDataWrapper);
}

bool MessageClientReqRegister::testSerializeDeserialize() {
    // Serialize
    MessageClientReqRegister messRegSe{};
    messRegSe.name = "qtuancr261";
    shared_ptr<uint8_t[]> data{};
    size_t dataSize{};
    messRegSe.serialize(data, dataSize);

    // Deserialize
    MessageClientReqRegister messRegDe{};
    messRegDe.deserialize(data, dataSize);

    assert(messRegSe == messRegDe);
    clog << "Passed Message::ClienReqRegister::testSerializeDeserialize()" << endl;
    return true;
}
bool MessageClientReqRegister::_serializeSpecHeader(BufferWrapper &buf) {
    // name: 4 byte size + data
    if (!buf.writeString(name)) return false;
    // serialize successfully when size remain equals to 0 byte
    return (buf.sizeRemain() == 0);
}

bool MessageClientReqRegister::_deserializeSpecHeader(BufferWrapper &buf) {
    // name: 4 byte size + data
    if (!buf.readString(name)) return false;
    // deserialize successfully when size remain equals to 0 byte
    return (buf.sizeRemain() == 0);
}

size_t MessageClientReqRegister::calculateFrameSize() const {
    return MessageClientBase::calculateFrameSize() + sizeof(uint32_t) /* 4 bytes size */ + name.size();
}
