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
}
void App::userMessageCallBack(net::TcpConnection& connection, net::SocketBuf& buf)
{
    User& user=userMap_.find(connection.getFd())->second;
    PARSE_RESULT handle_res=user.handleRquest(buf);
    if(user.getRequestType()==REQ_QUIT)
    {
        connection.destoryConn();
    }
    if(handle_res != NOT_ALL&&handle_res != NEED_DATA_BLOCK)
    {
        user.packResponse();
        connection.sendMessage(user.getResponse(),user.getResponseLength());
    }

}
void App::userCloseConn(net::TcpConnection& connection)
{
    printf("fd  %d closed connection \n",connection.getFd());
    userMap_.erase(connection.getFd());
}
