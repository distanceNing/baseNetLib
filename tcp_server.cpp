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
    int client_fd = -1;
    if((client_fd=serverSock_.Accept(conn_ip,conn_port)) < 0)
    {
        printErrorMsg("Accept");
    }
    printf("connect IP: %s ------ Port: %d\n", conn_ip, conn_port);

    //将新连接的客户端加入clientList
    clientList_.push_back(SocketFd());
    //设置关注事件和事件回调
    auto clientFd=&clientList_[clientList_.size() -1];
    clientFd->resetFd(client_fd);
    clientFd->setReadCallBack(clientCallBack_,clientFd);
    clientFd->setEvents(POLLIN);

    //再加入到pollList中,处理client发生的事件
    serverLoop_.addNewChannel(clientFd);
}

void TcpServer::serverStart()
{
    serverSock_.setEvents(POLLIN);
    serverSock_.setReadCallBack(connectionCallBack, this);
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
