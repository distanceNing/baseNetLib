//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"
void TcpServer::handleConnection(void *)
{
    char conn_ip[32];
    unsigned conn_port = 0;
    SocketFd client_sock;
    serverSock_.Accept(client_sock,conn_ip,conn_port);
    clientList_.push_back(client_sock);
    printf("connect IP: %s ------ Port: %d\n", conn_ip, conn_port);
}

void TcpServer::serverStart()
{
    serverLoop_.addNewChannel(&serverSock_);
    serverLoop_.startLoop();
}
