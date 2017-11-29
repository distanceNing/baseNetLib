//
// Created by yangning on 17-11-29.
//
// Descriprion :client连接类,消息的发送和消息的接收,并回调处理函数
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_TCPCONNECTION_H
#define BASE_NET_LIB_TCPCONNECTION_H
#include "common.h"
#include "socket/tcp_socket.h"
#include "channel.h"
#include "tcp_server.h"

#include <memory>
namespace {
class TcpSocket;
class EventLoop;
class TcpServer;
}
namespace net {

class TcpConnection {
public:
    TcpConnection(const int fd, const IpAddress& ipAddress, EventLoop* loop)
            :connSocket_(new TcpSocket(fd)), ipAddress_(ipAddress), connChannel_(loop, fd)
    {
        //添加connection的事件回调函数
        connChannel_.setReadCallBack(std::bind(&TcpConnection::handleRead, this));
        connChannel_.setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
        connChannel_.setErrorCallBack(errorCallBack_);
        //设置connsock可读
        connChannel_.enableReading();
    }

    void setClienReadCallBack(const TcpServer::ClientReadCallBack & call_back)
    {
        clientReadCallBack_ = call_back;
    }

    void setClienCloseCallBack(const TcpServer::ClientCloseCallBack & call_back)
    {
        closeCallBack_ = call_back;
    }

    void setClienErrorCallBack(const EventCallBack& call_back)
    {
        errorCallBack_ = call_back;
    }

    void handleRead();

    void handleClose()
    {
        connChannel_.removeSelf();
        connSocket_->closeFd();
    }

    void handleWrite();

    void sendMessage(const char* msg,size_t len);


    int getFd() const {
        return connSocket_->getFd();
    }

    ~TcpConnection()
    {
    }

private:
    std::unique_ptr<TcpSocket> connSocket_;
    Channel connChannel_;
    IpAddress ipAddress_;
    TcpServer::ClientReadCallBack clientReadCallBack_;
    TcpServer::ClientCloseCallBack closeCallBack_;
    EventCallBack errorCallBack_;
    SocketBuf readBuf_;
    SocketBuf writeBuf_;
};

} //namespace net
#endif //BASE_NET_LIB_TCPCONNECTION_H
