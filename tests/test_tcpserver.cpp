//
// Created by yangning on 17-10-25.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "../common.h"
#include "tcp_server.h"
#include "tcp_connection.h"
int main()
{
    net::EventLoop loop(net::POLL);

    net::TcpServer tcpServer(kPort,&loop);

    tcpServer.setClienCloseCallBack([](net::TcpServer::TcpConnectionPtr connection){
      printf("fd is %d closed \n",connection->getFd());
    });

    tcpServer.setClientReadCallBack([](net::TcpConnection& connection,net::SocketBuf* buf){
      connection.sendMessage(buf->readBegin(),buf->readableBytes());
      buf->skip(buf->readableBytes());
    });

    tcpServer.setClienErrorCallBack([](){
      printErrorMsg("error");
    });

    tcpServer.setNewConnCallBack([](int fd, const IpAddress& ipAddress) {
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
    });

    tcpServer.serverStart();

    return 0;
}

