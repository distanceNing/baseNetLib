//
// Created by yangning on 17-11-29.
//
// Descriprion :test echo server
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "Acceptor.h"
#include "common.h"
#include "tcp_server.h"
#include "tcp_connection.h"

int main()
{
    //std::cout<<sizeof (net::Channel);
    net::EventLoop loop(net::POLL);

    net::TcpServer tcpServer(kPort, &loop);

    tcpServer.setClienCloseCallBack([](net::TcpServer::TcpConnectionPtr connection){
      printf("fd is %d closed \n",connection->getFd());
    });

    tcpServer.setClientReadCallBack([](net::TcpConnection& connection,net::SocketBuf& buf){
      size_t readable=buf.readableBytes();
      std::vector<char> buffer(readable, 0);
      buf.read(buffer.data(), buffer.size());
      connection.sendMessage(buffer.data(), buffer.size());
    });

    tcpServer.setClienErrorCallBack([](){
      printErrorMsg("error");
    });

    tcpServer.setNewConnCallBack([](int fd, const IpAddress& ipAddress) {
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
    });

    tcpServer.serverStart();

    return EXIT_SUCCESS;
}