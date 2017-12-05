//
// Created by yangning on 17-12-5.
//
// Descriprion :加载配置 管理用户
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_APP_H
#define MEMCACHED_APP_H
#include "User.h"

#include <map>
#include "net/common.h"
namespace net{
class TcpConnection;
class SocketBuf;
};

class DataStructer;

class App {
protected:
    using UserMap=std::map<int ,User>;
public:
    App()
    {
    }

    void userCloseConn(net::TcpConnection& connection);

    void newUserConn(int fd,IpAddress ipAddress);

    void userMessageCallBack(net::TcpConnection& connection, net::SocketBuf& buf);
    ~App()
    {
    }
private:
    UserMap userMap_;
    DataStructer dataStructer_;
};

#endif //MEMCACHED_APP_H
