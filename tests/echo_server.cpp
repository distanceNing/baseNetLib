//
// Created by yangning on 17-11-29.
//
// Descriprion :test echo server
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "Acceptor.h"
#include "../common.h"
#include "tcp_server.h"

#include "tcp_connection.h"
void clientRCB(net::TcpConnection& connection, net::SocketBuf& buf)
{
    size_t readable=buf.readableBytes();
    std::vector<char> buffer(readable, 0);
    buf.read(buffer.data(), buffer.size());
    connection.sendMessage(buffer.data(), buffer.size());
}

void errorCB()
{
    printErrorMsg("read from fd");
}

void closecb(net::TcpConnection& connection)
{
    printf("Sockfd %d is close ---- \n", connection.getFd());
}
int main()
{
    //std::cout<<sizeof (net::Channel);
    net::EventLoop loop(net::POLL);

    net::TcpServer tcpServer(kPort, &loop);

    tcpServer.setClientReadCallBack(clientRCB);
    tcpServer.setClienErrorCallBack(errorCB);
    tcpServer.setClienCloseCallBack(closecb);
    tcpServer.serverStart();

    return EXIT_SUCCESS;
}