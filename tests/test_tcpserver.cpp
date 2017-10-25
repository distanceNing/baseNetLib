//
// Created by yangning on 17-10-25.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include "common.h"
#include "timerfdandsockfd/time_stamp.h"
#include "tcp_server.h"

void rcb(void* arg)
{
    auto socketFd = *static_cast<SocketFd*>(arg);
    char buffer[MAX_BUF_SIZE] = {'\0'};

    ssize_t size = socketFd.Receive(buffer, MAX_BUF_SIZE);

    if (size < 0) {
        printErrorMsg("Receive");
    }
    else if (size == 0) {
        printf("Sockfd %d is close ---- \n", socketFd.getFd());
        return;
    }
    else
    {
        socketFd.Send(buffer,size);
    }

}

int main()
{
    TimeStamp::printTimeNow();

    TcpServer tcpServer(POLL, kPort, rcb);
    tcpServer.serverStart();

    TimeStamp::printTimeNow();
    return 0;
}

