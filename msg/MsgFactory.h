//
// Created by yangning on 19-1-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_MSGFACTORY_H
#define BASE_NET_LIB_MSGFACTORY_H
#include "msg.h"
#include <memory>
class MsgFactory {
public:
    MsgFactory()
    {
    }

    static std::shared_ptr<Msg> createMsg(int type, int proto, std::string& content)
    {
        std::shared_ptr<Msg> msg_ptr(NULL);
        switch (type) {
        case Protocol::kAnnounceMsg : {
            msg_ptr.reset( new AnnounceMsg(content));
            msg_ptr->setMsgType(proto);
            break;
        }
        case Protocol::kInfoMsg: {
            msg_ptr.reset(new InfoMsg(content));
            msg_ptr->setMsgType(proto);
            break;
        }
        case Protocol::kRemindMsg: {
            msg_ptr.reset(new InfoMsg(content));
            msg_ptr->setMsgType(proto);
            break;
        }
        default:break;
        }
        return msg_ptr;
    }

    ~MsgFactory()
    {
    }

private:
};

#endif //BASE_NET_LIB_MSGFACTORY_H
