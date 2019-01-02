//
// Created by yangning on 18-1-15.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Server.h"
#include "tcp_server.h"
void Server::run()
{
    tcpServer_.serverStart();
    tcpServer_.setClienErrorCallBack([](){
      printErrorMsg("error");
    });

    tcpServer_.setClientReadCallBack([&](net::TcpConnection& connection,net::SocketBuf* buf){
      Session& session =  sessionMap_[net::TcpConnectionPtr(&connection)];
      session.parse(buf);

    });

    tcpServer_.setNewConnCallBack([&](int fd, const IpAddress& ipAddress,net::TcpConnectionPtr conn_ptr) {
      Session session;
      sessionMap_[conn_ptr]=std::move(session);
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
    });
}
Server::Server(net::EventLoop* loop)
        :tcpServer_(9000,loop)
{

}
