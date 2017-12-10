//
// Created by yangning on 17-11-29.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "tcp_connection.h"
namespace net {

TcpConnection::TcpConnection(const int fd, const IpAddress& ipAddress, EventLoop* loop)
        :connSocket_(fd), ipAddress_(ipAddress), connChannel_(loop, fd)
{
    //添加connection的事件回调函数
    connChannel_.setReadCallBack(std::bind(&TcpConnection::handleRead, this));
    connChannel_.setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
    connChannel_.setErrorCallBack(errorCallBack_);
    //设置connsock可读
    connChannel_.enableReading();
}

void TcpConnection::handleRead()
{
    ssize_t read_size;
    if ((read_size = readBuf_.readFromFd(connSocket_.getFd()) )> 0)
        clientReadCallBack_(*this, readBuf_);
    else if (read_size == 0)
        closeCallBack_(*this); //read 返回值为0,client关闭连接
    else
        errorCallBack_();
}

void TcpConnection::sendMessage(const char* msg, size_t len)
{
    assert(msg != NULL);
    ssize_t send_size;
    if ((send_size = connSocket_.Send(msg, len)) < len) {
        writeBuf_.write(msg + send_size, len - send_size);
        connChannel_.enableWriting();
    }
}
void TcpConnection::handleClose()
{
    connChannel_.removeSelf();
    connChannel_.disenableEvent();
    connSocket_.closeFd();
}
void TcpConnection::handleWrite()
{
    size_t readable = writeBuf_.readableBytes();
    ssize_t size = connSocket_.Send(writeBuf_.readBegin(), readable);
    if (size < 0) {
        errorCallBack_();
        return;
    }
    writeBuf_.skip((size_t) size);
    if (size == readable)
        connChannel_.disenableWriting();

}

}//namespace net