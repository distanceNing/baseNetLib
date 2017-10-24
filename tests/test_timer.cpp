//
// Created by yangning on 17-10-23.
//

#include "event_loop.h"
#include "net_helper/tcp_socket.h"
#include "common.h"
#include "timerfd/time_stamp.h"
#include "timerfd/timer.h"

EventLoop* g_loop;

void timeRCB(int fd)
{
    int64_t error;
    size_t size = read(fd, &error, sizeof(error));
    printf("timeRCB read  size is : %lu\n", size);
    g_loop->quitLoop();
}


int main()
{
    TimeStamp::printTimeNow();
    //建立监听socket
    //TcpSocket server_sock;
    //server_sock.CreateSocket(AF_INET, SOCK_STREAM, kPort);
    //server_sock.Listen();
    //Channel channel(server_sock.GetSocket(), rcb);

    Timer timer;
    timer.createTimer();
    //第一个参数为第一次timerfd触发的时间(从现在开始 单位:s)
    timer.setTime(4, 4);
    Channel channel(timer.getTimerFd(),timeRCB);
    channel.setEvent(POLLIN);
    EventLoop main_loop;
    main_loop.addNewChannel(&channel);
    g_loop = &main_loop;
    main_loop.startLoop();



    TimeStamp::printTimeNow();
    return 0;
}

