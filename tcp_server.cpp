//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"
namespace net {
TcpServer::TcpServer(POLL_TYPE pollType, int listenPort)
        :serverLoop_(pollType), serverSock_(&serverLoop_)
{
    if (!serverSock_.CreateSocket(listenPort))
        printErrorMsg("CreateSocket");
    serverSock_.Listen();
}



void TcpServer::serverStart()
{
    serverSock_.setEvents(POLLIN);
    Fd::EventCallBack fun=std::bind(connectionCallBack,this);
    serverSock_.setReadCallBack(fun);
    serverLoop_.addNewChannel(&serverSock_);
    serverLoop_.startLoop();
}

void TcpServer::serverStop()
{
    serverLoop_.quitLoop();
}

void TcpServer::connectionCallBack(void* arg)
{
    TcpServer* tcpServer = static_cast<TcpServer*>(arg);
    tcpServer->handleConnection();
}

TcpServer::~TcpServer()
{
    serverSock_.closeFd();
}
} //namespace net