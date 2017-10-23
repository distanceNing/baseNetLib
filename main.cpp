#include "print_time.h"
#include "event_loop.h"
#include "net_helper/tcp_socket.h"
#include "common.h"
const int kPort = 8000;

void wcb(int fd)
{
    char buffer[] = "hello world";
    size_t size = write(fd, buffer, strlen(buffer));
    printf("writeable write size is : %lu\n", size);
}

void rcb(int listen_fd)
{
    int client_fd = -1;
    char connIP[32];
    socklen_t clilen;
    struct sockaddr_in client_addr;
    clilen = sizeof(client_addr);
    memset(&client_addr, 0, sizeof(client_addr));
    if ((client_fd = accept(listen_fd, (struct sockaddr*) &client_addr, &clilen))<0) {
        printErrorMsg("accept");
    }
    memset(connIP, '\0', 32);
    strcpy(connIP, inet_ntoa(client_addr.sin_addr));
    printf("connect IP: %s ------ Port: %d\n", connIP, ntohs(client_addr.sin_port));
}

int main()
{
    time_t start_time = time(0);
    struct tm* tm = localtime(&start_time);
    printf("server start time :%d : %d : %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec);

    //建立监听socket
    TcpSocket server_sock;
    server_sock.CreateSocket(AF_INET, SOCK_STREAM, kPort);
    server_sock.Listen();

    Channel channel(server_sock.GetSocket(), rcb);
    channel.setEvent(POLLIN);

    EventLoop main_loop;
    main_loop.addNewChannel(&channel);
    main_loop.startLoop();

    time_t end_time = time(0);
    tm = localtime(&end_time);
    printf("server end time :%d : %d : %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec);
    return 0;
}
