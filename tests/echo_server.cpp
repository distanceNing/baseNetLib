//
// Created by yangning on 17-10-25.
//
// Descriprion : main func 基于事件驱动基础网络库
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "common.h"
#include "tcp_server.h"

void clientRCB(net::Channel* channel)
{
    net::TcpSocket sock(channel->getFd());
    char buffer[MAX_BUF_SIZE] = {'\0'};
    ssize_t size = sock.Receive(buffer, MAX_BUF_SIZE);

    if (size < 0) {
        printErrorMsg("Receive");
    }
    else if (size == 0) {
        printf("Sockfd %d is close ---- \n", sock.getFd());
        sock.closeFd();
        channel->removeSelf();
        return;
    }
    else {
        sock.Send(buffer, static_cast<size_t>(size));
    }
}

class EchoServer : public net::TcpServer {
public:
    EchoServer(net::POLL_TYPE pollType, int listenPort)
            :TcpServer(pollType, listenPort)
    {
    }



};

int main()
{
    net::TimeStamp::printTimeNow();

    EchoServer tcpServer(net::POLL, kPort);
    tcpServer.serverStart();

    net::TimeStamp::printTimeNow();
    return 0;
}

