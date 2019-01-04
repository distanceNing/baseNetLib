//
// Created by yangning on 19-1-2.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef THEAPP_MSG_H
#define THEAPP_MSG_H
#include <string>
#include "../proto/Protocol.h"
//消息传输类型
class MsgProto {
public:
    MsgProto(const std::string& type)
    {
    }

    const std::string& getMsgType() const
    {
        return msg_type_;
    }

    virtual void subscribemessImp()
    {
    }

protected:
    std::string msg_type_;
};
class XML : public MsgProto {
public:
    XML() :MsgProto("Xml")
    {
    }
    void subscribemessImp();
};
class HTML : public MsgProto {
public:
    HTML() :MsgProto("Html")
    {
    }
    void subscribemessImp();
};
class JSON : public MsgProto {
public:
    JSON()
            :MsgProto("Json")
    {
    }

    void subscribemessImp();
};
//消息 MSG
class Msg {
public:
    Msg(const std::string& content,int type):content_(content),msg_type_(type){
    }
    virtual void subscribe()
    {
    }

    void setMsgType(int msg_type);

    std::string packMsg(const std::string& content);


protected:
    MsgProto* msg_proto_;
    int msg_proto_num_;
    std::string content_;
    int msg_type_;
};
//通告
class AnnounceMsg : public Msg {
public:
    AnnounceMsg(const std::string& content):Msg(content,Protocol::kAnnounceMsg)
    {}

    void subscribe() override
    {
        msg_proto_->subscribemessImp();
    }
};
//提醒
class RemindMsg : public Msg {
public:
    RemindMsg(const std::string& content):Msg(content,Protocol::kRemindMsg)
    {}
    void subscribe() override
    {
        msg_proto_->subscribemessImp();
    }
};
//信息
class InfoMsg : public Msg {
public:
    InfoMsg(const std::string& content):Msg(content,Protocol::kInfoMsg)
    {}

    void subscribe() override
    {
        msg_proto_->subscribemessImp();
    }
};
#endif //THEAPP_MSG_H
