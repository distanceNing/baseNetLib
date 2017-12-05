//
// Created by yangning on 17-12-5.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "app.h"
#include "net/tcp_connection.h"

void App::newUserConn(int fd,IpAddress ipAddress)
{
    userMap_.insert(std::make_pair(fd,User(&dataStructer_)));
    printf("connect IP: %s ------ Port: %d\n", ipAddress.ip.c_str(), ipAddress.port);
}
void App::userMessageCallBack(net::TcpConnection& connection, net::SocketBuf& buf)
{
    User& user=userMap_.find(connection.getFd())->second;
}
