//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include <functional>
#include <list>
class TcpServer {
public:
    TcpServer(POLL_TYPE pollType,int listenPort,Fd::EventCallBack clientCallBack);

    static void connectionCallBack(void* arg);

    void handleConnection();

    void serverStart();

    void serverStop();

    ~TcpServer();

protected:
    using ClientList=std::list<SocketFd>;
private:
    Fd::EventCallBack clientCallBack_;
    EventLoop serverLoop_;
    SocketFd serverSock_;
    ClientList clientList_;
};

#endif //BASE_NET_LIB_TCPSERVER_H
