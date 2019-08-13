/*
 * Author: tuantq3
 * File: messagedef.h
 *
 * Created on 13/8/2019
 */
#ifndef MESSAGEDEF_H
#define MESSAGEDEF_H

#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
enum class MsgType {
    REQ_REGISTER = 0,
    RES_REGISTER = 1,
};

using FrameSize = int32_t;
using ProtocolVersion = int8_t;
using MessageType = int8_t;
using SeqId = int64_t;
#endif  // MESSAGEDEF_H
