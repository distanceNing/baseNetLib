//
// Created by yangning on 17-10-25.
//
// Descriprion : main func 基于事件驱动基础网络库
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include "common.h"
#include "timerfdandsockfd/time_stamp.h"
#include "tcp_server.h"

void clientRCB(net::SocketFd* socketFd)
{
    char buffer[MAX_BUF_SIZE] = {'\0'};
    ssize_t size = socketFd->Receive(buffer, MAX_BUF_SIZE);

    if (size < 0) {
        printErrorMsg("Receive");
    }
    else if (size == 0) {
        printf("Sockfd %d is close ---- \n", socketFd->getFd());
        socketFd->closeFd();
        socketFd->removeSelf();
        return;
    }
    else {
        socketFd->Send(buffer, static_cast<size_t>(size));
    }
}

class EchoServer : public net::TcpServer {
public:
    EchoServer(net::POLL_TYPE pollType, int listenPort)
            :TcpServer(pollType, listenPort)
    {
    }

    void handleConnection() override
    {
        char conn_ip[32];
        unsigned conn_port = 0;
        int client_fd = -1;
        if ((client_fd = serverSock_.Accept(conn_ip, conn_port)) < 0) {
            printErrorMsg("Accept");
        }
        printf("connect IP: %s ------ Port: %d\n", conn_ip, conn_port);

        //将新连接的客户端加入clientList
        clientList_.push_back(net::SocketFd(&serverLoop_));


        //设置关注事件和事件回调
        auto clientFd = &clientList_.back();
        clientFd->resetFd(client_fd);
        net::Fd::EventCallBack fun = std::bind(clientRCB, clientFd);
        clientFd->setReadCallBack(fun);
        clientFd->setEvents(POLLIN);

        //再加入到pollList中,处理client发生的事件
        serverLoop_.addNewChannel(clientFd);
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

