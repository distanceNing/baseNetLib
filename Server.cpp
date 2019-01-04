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

    tcpServer_.setClienErrorCallBack([](){
      printErrorMsg("error");
    });

    tcpServer_.setClientReadCallBack([&](net::TcpConnectionPtr connection,net::SocketBuf* buf){
     auto ite =  sessionMap_.find(connection->getFd())->second;//[net::TcpConnectionPtr(&connection)];
     ite.handleRequest(connection,buf);

    });


    tcpServer_.setClienCloseCallBack([](net::TcpConnectionPtr connection){
      printf("fd is %d closed \n",connection->getFd());
    });



    tcpServer_.setNewConnCallBack([&](int fd, const IpAddress& ipAddress,net::TcpConnectionPtr& conn_ptr) {
      //Session session(ipAddress);
      sessionMap_.insert(std::make_pair(fd,Session(ipAddress)));
      //sessionMap_[conn_ptr]=std::move(session);
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
    });

    tcpServer_.serverStart();
}
Server::Server(net::EventLoop* loop,size_t thread_num)
        :tcpServer_(9000,loop,thread_num)
{

}
