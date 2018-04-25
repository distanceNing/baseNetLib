//
// Created by yangning on 17-11-29.
//
// Descriprion :client连接类,消息的发送和消息的接收,并回调处理函数
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_TCPCONNECTION_H
#define BASE_NET_LIB_TCPCONNECTION_H

#include "tcp_server.h"
#include "include/common.h"
#include "socket/tcp_socket.h"
#include "socket/socket_buf.h"

#include <memory>

namespace net {

class EventLoop;
class Channel;


class TcpConnection :public std::enable_shared_from_this<TcpConnection>{
public:
    enum ConnectState {
      kConnecting, kConnected, kdisConnecting, kdisConnected
    };

    TcpConnection(const int fd, const IpAddress& ipAddress, EventLoop* loop);

    void setClienReadCallBack(const ClientReadCallBack& call_back)
    {
        clientReadCallBack_ = call_back;
    }

    void setClienCloseCallBack(const ClientCloseCallBack& call_back)
    {
        closeCallBack_ = call_back;

    }

    void setClienErrorCallBack(const EventCallBack& call_back)
    {
        errorCallBack_ = call_back;

    }
    //提供给上层调用的发送消息函数
    //线程安全的
    void send(const char* msg, size_t len);

    void shutdown();

    // *InLoop 保证在IO线程之中调用
    void sendInLoop(const std::string& msg);

    void shutdownInLoop();


    bool isConnected() const
    {
        return connectState_ == kConnected;
    }

    int getFd() const
    {
        return connSocket_.getFd();
    }

    void enableConnection();

    void destoryConn();

    ~TcpConnection()
    {
        connSocket_.closeFd();
    }

private:
    void handleRead();

    void handleWrite();

    void handleClose();

    EventLoop* loop_;
    ConnectState connectState_;
    TcpSocket connSocket_;
    Channel connChannel_;
    IpAddress ipAddress_;
    ClientReadCallBack clientReadCallBack_;
    ClientCloseCallBack closeCallBack_;
    EventCallBack errorCallBack_;
    SocketBuf readBuf_;
    SocketBuf writeBuf_;
};

} //namespace net
#endif //BASE_NET_LIB_TCPCONNECTION_H
