//
// Created by yangning on 19-1-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_MSGSET_H
#define BASE_NET_LIB_MSGSET_H

#include <vector>

#include "msg.h"
class MsgSet {
public:
    MsgSet()
    {
    }

    bool pushMsg()
    {
        return false;
    }

    std::vector<Msg*> getMsg(int type);

    ~MsgSet()
    {
    }

private:
};

#endif //BASE_NET_LIB_MSGSET_H
