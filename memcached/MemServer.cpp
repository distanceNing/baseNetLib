//
// Created by yangning on 17-12-5.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "MemServer.h"
#include "net/tcp_connection.h"

void MemServer::newUserConn(int fd,IpAddress ipAddress)
{
    userMap_.insert(std::make_pair(fd,User(&dataStructer_)));
}
void MemServer::userMessageCallBack(net::TcpConnection& connection, net::SocketBuf& buf)
{
    User& user=userMap_.find(connection.getFd())->second;
    PARSE_RESULT handle_res=user.handleRquest(buf);
    if(user.getRequestType()==REQ_QUIT)
    {
        connection.destoryConn();
        return;
    }
    if(handle_res != NOT_ALL&&handle_res != NEED_DATA_BLOCK)
    {
        user.packResponse(handle_res);
        connection.sendMessage(user.getResponse(),user.getResponseLength());
    }

}
void MemServer::userCloseConn(net::TcpConnection& connection)
{
    printf("fd  %d closed connection \n",connection.getFd());
    userMap_.erase(connection.getFd());
}
