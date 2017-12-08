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
#include "../net/common.h"
#include "../net/tcp_server.h"

class DataStructer;

class App {
protected:
    using UserMap=std::map<int ,User>;
public:
    App(net::EventLoop* loop):tcpServer_(kPort,loop)
    {
        tcpServer_.setClientReadCallBack(std::bind(&App::userMessageCallBack,this,_1,_2));
        tcpServer_.serNewConnCallBack(std::bind(&App::newUserConn,this,_1,_2));
        tcpServer_.setClienCloseCallBack(std::bind(&App::userCloseConn,this,_1));
    }

    void run()
    {
        tcpServer_.serverStart();
    }

    ~App()
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
