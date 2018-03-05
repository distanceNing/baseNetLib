//
// Created by yangning on 17-10-25.
//
#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include "../common.h"
#include "timerfdandsockfd/time_stamp.h"
#include "tcp_server.h"

EventLoop* g_loop;


void rcb(void* fd)
{
    SocketFd listen_fd = *static_cast<SocketFd*>(fd);
    char connIP[32];
    unsigned conn_port=0;
    SocketFd client_sock;
    if (!listen_fd.Accept(client_sock,connIP,conn_port))
    {
        printErrorMsg("accept");
    }
    printf("connect IP: %s ------ Port: %d\n", connIP, conn_port);
    g_loop->quitLoop();
}

int main()
{
    TimeStamp::printTimeNow();
    //建立监听socket
    SocketFd server_sock;
    if(!server_sock.CreateSocket(kPort))
    {
        printErrorMsg("socket");
    }
    server_sock.Listen();

    EventLoop main_loop(EPOLL);
    server_sock.setEvents(POLLIN);
    server_sock.setReadCallBack(&rcb);
    main_loop.addNewChannel(&server_sock);
    g_loop = &main_loop;
    main_loop.startLoop();

    TimeStamp::printTimeNow();
    return 0;
}

