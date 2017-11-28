//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_ACCEPTOR_H
#define BASE_NET_LIB_ACCEPTOR_H

#include "socket/tcp_socket.h"
#include "common.h"
#include "channel.h"


namespace  net {

class Acceptor {
public:
    Acceptor(int listenPort,EventLoop* loop):listenSock_(TcpSocket::create_and_bind(listenPort)),
                             listenChannel_(loop,listenSock_.getFd())
    {

    }

    void handleRead();


    ~Acceptor()
    {
    }

private:
    TcpSocket listenSock_;
    bool listening_;
    Channel listenChannel_;
};
}
#endif //BASE_NET_LIB_ACCEPTOR_H
