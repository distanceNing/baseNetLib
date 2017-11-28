//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include <functional>
#include <list>
#include "channel.h"
#include "socket/tcp_socket.h"
#include "Acceptor.h"
namespace net{
class TcpServer {
public:
    TcpServer(POLL_TYPE pollType,int listen_port);

    static void connectionCallBack(void* arg);

    virtual void handleConnection()=0;

    void serverStart();

    void serverStop();

    ~TcpServer();

protected:
    using ClientList=std::list<Channel>;
protected:
    EventLoop serverLoop_;
    net::Acceptor acceptor_;
    ClientList clientList_;
};
}//namespace net
#endif //BASE_NET_LIB_TCPSERVER_H
