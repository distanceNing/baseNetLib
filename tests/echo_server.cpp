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

void clientRCB(void* arg)
{
    auto socketFd = static_cast<SocketFd*>(arg);
    char buffer[MAX_BUF_SIZE] = {'\0'};

    ssize_t size = socketFd->Receive(buffer, MAX_BUF_SIZE);

    if (size < 0)
    {
        printErrorMsg("Receive");
    }
    else if (size == 0)
    {
        printf("Sockfd %d is close ---- \n", socketFd->getFd());
        socketFd->closeFd();
        socketFd->removeSelf();
        return;
    }
    else
    {
        socketFd->Send(buffer, static_cast<size_t>(size));
    }
}

int main()
{
    TimeStamp::printTimeNow();

    TcpServer tcpServer(POLL, kPort, clientRCB);
    tcpServer.serverStart();

    TimeStamp::printTimeNow();
    return 0;
}

