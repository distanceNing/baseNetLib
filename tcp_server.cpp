//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"

TcpServer::TcpServer(POLL_TYPE pollType, int listenPort,Fd::EventCallBack clientCallBack)
        :serverLoop_(pollType),clientCallBack_(clientCallBack)
{
    if(!serverSock_.CreateSocket(listenPort))
        printErrorMsg("CreateSocket");
    serverSock_.Listen();
}

void TcpServer::handleConnection()
{
    char conn_ip[32];
    unsigned conn_port = 0;
    SocketFd client_sock;
    serverSock_.Accept(client_sock,conn_ip,conn_port);
    printf("connect IP: %s ------ Port: %d\n", conn_ip, conn_port);

    //将新连接的客户端加入clientList
    clientList_.push_back(client_sock);

    //再加入到pollList中,处理client发生的事件
    client_sock.setReadCallBack(clientCallBack_,&client_sock);
    client_sock.setEvents(POLLIN);
    serverLoop_.addNewChannel(&client_sock);
}

void TcpServer::serverStart()
{
    serverSock_.setEvents(POLLIN);
    serverSock_.setReadCallBack(connectionCallBack,this);
    serverLoop_.addNewChannel(&serverSock_);
    serverLoop_.startLoop();
}

void TcpServer::serverStop()
{
    serverLoop_.quitLoop();
}

void TcpServer::connectionCallBack(void* arg)
{
    TcpServer* tcpServer= static_cast<TcpServer*>(arg);
    tcpServer->handleConnection();
}
