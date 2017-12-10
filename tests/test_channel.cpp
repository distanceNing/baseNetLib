//
// Created by yangning on 17-10-25.
//
#include "event_loop.h"
#include "tcp_server.h"
#include "timerfd/time_stamp.h"

void rcb(int fd)
{
    net::TcpSocket listen_fd(fd);
    char connIP[32];
    unsigned conn_port=0;
    int client_sock;
    if ((client_sock=listen_fd.Accept(connIP,conn_port)) < 0)
    {
        printErrorMsg("accept");
    }
    printf("connect IP: %s ------ Port: %d\n", connIP, conn_port);
    exit(0);
}

int main()
{
    net::TimeStamp::printTimeNow();
    //建立监听socket
    net::TcpSocket server_sock;
    if(!server_sock.CreateSocket(kPort))
    {
        printErrorMsg("socket");
    }
    server_sock.Listen();

    net::EventLoop main_loop(net::POLL);

    net::Channel channel(&main_loop,server_sock.getFd());
    channel.setReadCallBack(std::bind(rcb,server_sock.getFd()));
    channel.enableReading();
    main_loop.startLoop();

    net::TimeStamp::printTimeNow();
    return 0;
}

