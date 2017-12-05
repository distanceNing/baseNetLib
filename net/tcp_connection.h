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
#include "tcp_server.h"

#include <memory>
namespace net{
class TcpSocket;
class EventLoop;
class Channel;
}
namespace net {

class TcpConnection {
public:
    TcpConnection(const int fd, const IpAddress& ipAddress, EventLoop* loop);

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

    void sendMessage(const char* msg,size_t len);

    int getFd() const {
        return connSocket_->getFd();
    }

    void handleRead();

    void handleClose();

    void handleWrite();


    uint32_t getConnPort()const
    {
        return ipAddress_.port;
    }

    const std::string& getConnIp()const
    {
        return ipAddress_.ip;
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
