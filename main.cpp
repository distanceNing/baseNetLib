#include "event_loop.h"
#include "net_helper/tcp_socket.h"
#include "common.h"
#include "timerfd/time_stamp.h"
#include "tcp_server.h"
EventLoop* g_loop;


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

    //channel.setEvents(POLLIN);
    //EventLoop main_loop(EPOLL);
    //main_loop.addNewChannel(&channel);
    //g_loop = &main_loop;
    //main_loop.startLoop();
    TcpServer tcpServer(POLL,kPort);
    tcpServer.serverStart();
    TimeStamp::printTimeNow();
    return 0;
}
