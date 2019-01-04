//
// Created by yangning on 18-1-14.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef THEAPP_SESSION_H
#define THEAPP_SESSION_H
#include "tcp_connection.h"
#include "msg/msg.h"
#include <string>
#include <memory>
#include <set>
#include <rapidjson/document.h>

#include "common.h"
using JsonType = std::shared_ptr<rapidjson::Document>;
class Session {
public:
    enum kProcessState {
      kUpload, kDownload, kSendFileBlock, kRecvFileBlock
    };



    Session(const IpAddress& address)
    {
    }


    void handleRequest(net::TcpConnectionPtr& connection, net::SocketBuf* buf);

    std::string  parse(net::SocketBuf* buf);

    std::string process(const std::string& json,net::TcpConnectionPtr& connection);

    ~Session()
    {
    }

private:
    bool push2Consumer(std::map<std::string,std::string>& json_map);

    bool handleRegister(net::TcpConnectionPtr& connection,int type);

    bool handlePushMsg(int type,int proto,const std::string& content);

    kProcessState processState_;
    std::set<std::shared_ptr<Msg>> msgSet_;

};

#endif //THEAPP_SESSION_H
