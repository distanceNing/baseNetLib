//
// Created by yangning on 17-12-5.
//
// Descriprion :加载配置 管理用户
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_APP_H
#define MEMCACHED_APP_H
#include "user.h"

#include <map>
#include "net/common.h"
#include "net/tcp_server.h"

class DataStructer;

class MemServer {
protected:
    using UserMap=std::map<int ,User>;
public:
    MemServer(net::EventLoop* loop):tcpServer_(kPort,loop)
    {
        tcpServer_.setClientReadCallBack(std::bind(&MemServer::userMessageCallBack,this,_1,_2));
        tcpServer_.setNewConnCallBack(std::bind(&MemServer::newUserConn,this,_1,_2));
        tcpServer_.setClienCloseCallBack(std::bind(&MemServer::userCloseConn,this,_1));
    }

    void run()
    {
        tcpServer_.serverStart();
    }

    ~MemServer()
    {
    }
private:
    void userCloseConn(net::TcpConnection& connection);

    void newUserConn(int fd,IpAddress ipAddress);

    void userMessageCallBack(net::TcpConnection& connection, net::SocketBuf& buf);
    UserMap userMap_;
    DataStructer dataStructer_;
    net::TcpServer tcpServer_;
};

#endif //MEMCACHED_APP_H
