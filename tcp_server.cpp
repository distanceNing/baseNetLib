//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"
namespace net {
TcpServer::TcpServer(POLL_TYPE pollType,int listen_port)
        :serverLoop_(pollType),acceptor_(listen_port,&serverLoop_)
    {

    }



void TcpServer::serverStart()
{
    serverChannel_.setEvents(POLLIN);
    net::EventCallBack fun=std::bind(connectionCallBack,this);
    serverChannel_.setReadCallBack(fun);
    serverLoop_.addNewChannel(&serverChannel_);
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