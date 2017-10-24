#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include "common.h"
#include "timerfdandsockfd/time_stamp.h"
#include "tcp_server.h"

EventLoop* g_loop;


void rcb(void* fd)
{
    int listen_fd = *static_cast<int*>(fd);
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

    EventLoop main_loop(POLL);
    server_sock.setEvents(POLLIN);
    server_sock.setReadCallBack(&rcb);
    main_loop.addNewChannel(&server_sock);
    g_loop = &main_loop;
    main_loop.startLoop();

    TimeStamp::printTimeNow();
    return 0;
}
