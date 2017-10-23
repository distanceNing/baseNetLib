#include "event_loop.h"
#include "net_helper/tcp_socket.h"
#include "common.h"
#include "timerfd/time_stamp.h"
#include "timerfd/timer.h"

void timeRCB(int fd)
{
    int64_t error;
    size_t size = read(fd, &error, sizeof(error));
    printf("readable  size is : %lu\n", size);
}

void rcb(int listen_fd)
{
    int client_fd = -1;
    char connIP[32];
    socklen_t clilen;
    struct sockaddr_in client_addr;
    clilen = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(client_addr));
    if ((client_fd = accept(listen_fd, (struct sockaddr*) &client_addr, &clilen)) < 0) {
        printErrorMsg("accept");
    }
    memset(connIP, '\0', 32);
    strcpy(connIP, inet_ntoa(client_addr.sin_addr));
    printf("connect IP: %s ------ Port: %d\n", connIP, ntohs(client_addr.sin_port));
}

int main()
{
    TimeStamp::printTimeNow();
    //建立监听socket
    //TcpSocket server_sock;
    //server_sock.CreateSocket(AF_INET, SOCK_STREAM, kPort);
    //server_sock.Listen();
    Timer timer;
    timer.createTimer();
    timer.setTime(4, 4);

    uint64_t error = 0;
    for (int i = 0; i < 10; ++i)
    {
        ssize_t read_size = read(timer.getTimerFd(), &error, sizeof(uint64_t));
        if (read_size != sizeof(uint64_t)) {
             perror("read error");
        }
        TimeStamp::printTimeNow();
    }
    //Channel channel(server_sock.GetSocket(), rcb);
    //channel.setEvent(POLLIN);
    //Channel channel(timer.getTimerFd(),timeRCB);
    //EventLoop main_loop;
    //main_loop.addNewChannel(&channel);
    //main_loop.startLoop();





    return 0;
}
