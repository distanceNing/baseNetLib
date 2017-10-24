//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include "timerfdandsockfd/socket_fd.h"

class TcpServer {
public:
    TcpServer(POLL_TYPE pollType,int listenPort):serverLoop_(pollType)
    {
        serverSock_.CreateSocket(listenPort);
        serverSock_.Listen();

    }

    void handleConnection(void *);


    void serverStart();

    void serverStop()
    {
        serverLoop_.quitLoop();
    }

    ~TcpServer(){
        serverSock_.CloseSocket();
    }
protected:
    using ClientList=std::vector<SocketFd>;
private:
    EventLoop serverLoop_;
    SocketFd serverSock_;
    ClientList clientList_;
};

#endif //BASE_NET_LIB_TCPSERVER_H
