//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include "net_helper/tcp_socket.h"

class TcpServer {
public:
    TcpServer(POLL_TYPE pollType,int listenPort):serverLoop_(pollType)
    {
        serverSock_.CreateSocket(listenPort);
        serverSock_.Listen();

    }

    void handleConnection(void *);


    void serverStart()
    {
        serverChannel_=new  Channel(serverSock_.GetSocket(),handleConnection);
        serverChannel_->setEvents(POLLIN);
        serverLoop_.addNewChannel(serverChannel_);
        serverLoop_.startLoop();
    }

    void serverStop()
    {
        serverLoop_.quitLoop();
    }

    ~TcpServer(){
        serverSock_.CloseSocket();
    }
protected:
    using ClientList=std::vector<TcpSocket>;
private:
    EventLoop serverLoop_;
    TcpSocket serverSock_;
    Channel* serverChannel_;
    ClientList clientList_;
};

#endif //BASE_NET_LIB_TCPSERVER_H
