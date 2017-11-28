//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"
#include <functional>
#include <list>
namespace net{
class TcpServer {
public:
    TcpServer(POLL_TYPE pollType,int listenPort);

    static void connectionCallBack(void* arg);

    virtual void handleConnection()=0;

    void serverStart();

    void serverStop();

    ~TcpServer();

protected:
    using ClientList=std::list<SocketFd>;
protected:
    EventLoop serverLoop_;
    SocketFd serverSock_;
    ClientList clientList_;
};
}//namespace net
#endif //BASE_NET_LIB_TCPSERVER_H
