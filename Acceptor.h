//
// Created by yangning on 17-11-28.
//
// Descriprion : acceptor 用来接受连接,当有连接到来时,调用NewConnetcionCallBack来通知tcpserer.
//               是tcpserver的内部类.
//              起初设计的时时候没有把acceptor和tcpserver分开,在tcpserver中做了acceptor的事情,那样类的分工不明确.
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_ACCEPTOR_H
#define BASE_NET_LIB_ACCEPTOR_H

#include "socket/tcp_socket.h"
#include "include/common.h"
#include "channel.h"

#include <functional>
#include <iostream>

namespace net {
class  EventLoop;

using NewConnetcionCallBack=std::function<void(int, const IpAddress&)>;
class Acceptor {
public:
    Acceptor(unsigned listenPort, EventLoop* loop);

    void listen();

    void setNewConnetcionCallBack(const NewConnetcionCallBack& cb)
    {
        newConnetcioncb_ = cb;
    }

    void handleRead();

    bool listening() const
    {
        return listening_;
    }

    ~Acceptor()
    {
    }

private:
    EventLoop* ownEventLoop_;
    TcpSocket listenSock_;
    unsigned listenPort_;
    bool listening_;
    Channel listenChannel_;
    NewConnetcionCallBack newConnetcioncb_;
};
}
#endif //BASE_NET_LIB_ACCEPTOR_H
