//
// Created by yangning on 17-10-24.
//
// Descriprion : tcpserver 内部持有acceptor来接收连接,以及管理连接
//
// Copyright (c) yangning All rights reserved.
//
#ifndef BASE_NET_LIB_TCPSERVER_H
#define BASE_NET_LIB_TCPSERVER_H
#include "event_loop.h"
#include "socket/tcp_socket.h"
#include "channel.h"
#include "Acceptor.h"

#include <functional>
#include <list>
#include <memory>

using namespace std::placeholders;
namespace net {
class SocketBuf;
class TcpConnection;
}

namespace net {

class TcpServer {
public:
    using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
    using ConnectionMap=std::map<int, TcpConnectionPtr>;
public:
    using ClientReadCallBack=std::function<void(TcpConnection&, SocketBuf&)>;
    using ClientCloseCallBack=std::function<void(TcpConnectionPtr)>;
    using NewConnCallBack =std::function<void(int, const IpAddress&)>;

    TcpServer(unsigned listen_port, EventLoop* loop);

    void newConnectionCallBack(int fd, IpAddress ip_address);

    void setNewConnCallBack(const NewConnCallBack& call_back)
    {
        newConnCallBack_ = call_back;
    }

    void setClientReadCallBack(const ClientReadCallBack& call_back)
    {
        clienReadCallBack_ = call_back;
    }

    void setClienCloseCallBack(const ClientCloseCallBack& call_back)
    {
        closeCallBack_ = call_back;
    }

    void setClienErrorCallBack(const EventCallBack& call_back)
    {
        errorCallBack_ = call_back;
    }

    void removeConnection(TcpConnectionPtr connection);

    void serverStart();

    void serverStop();

    ~TcpServer()
    {
    }


protected:
    Acceptor::NewConnetcionCallBack cb;
    EventLoop* serverLoop_;
    std::unique_ptr<Acceptor> acceptor_;
    ConnectionMap connectionMap_;
    ClientReadCallBack clienReadCallBack_;
    ClientCloseCallBack closeCallBack_;
    NewConnCallBack newConnCallBack_;
    EventCallBack errorCallBack_;
};
}//namespace net
#endif //BASE_NET_LIB_TCPSERVER_H
