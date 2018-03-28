//
// Created by yangning on 17-11-29.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "tcp_connection.h"
#include "event_loop.h"
namespace net {

TcpConnection::TcpConnection(const int fd, const IpAddress& ipAddress, EventLoop* loop)
        :loop_(loop),connSocket_(fd), ipAddress_(ipAddress), connChannel_(loop, fd), connectState_(kConnected)
{
    //添加connection的事件回调函数
    connChannel_.setReadCallBack(std::bind(&TcpConnection::handleRead, this));
    connChannel_.setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
    connChannel_.setCloseCallBack(std::bind(&TcpConnection::handleClose, this));
    connChannel_.setErrorCallBack(errorCallBack_);
    //设置connsock可读
    connChannel_.enableReading();
}

void TcpConnection::handleRead()
{
    assert(isConnected());
    ssize_t read_size;
    if ((read_size = readBuf_.readFromFd(connSocket_.getFd())) > 0 ) {
        clientReadCallBack_(*this, &readBuf_);
    }//EOF
    else if ( read_size == 0 ) {
        if ( writeBuf_.readableBytes() > 0 ) {
            //当还有未发送完的用户数据时,先对数据进行发送,之后在正确关闭连接.
            //connectState_ = kdisConnecting;
            ssize_t send_size = -1;
            size_t readable = writeBuf_.readableBytes();
            if ((send_size = connSocket_.Send(writeBuf_.readBegin(), readable)) < readable ) {
                //发送write buffer中的数据,一次发送未发送完毕,关注可写事件
                connChannel_.enableWriting();
            }
            writeBuf_.skip((size_t) send_size);
        }
        //read 返回值为0且发送缓冲区中没有数据时,关闭连接
        if ( writeBuf_.readableBytes() == 0 )
            handleClose();
    }
    else
        errorCallBack_();
}

void TcpConnection::send(const char* msg, size_t len)
{
    assert(msg != NULL);
    std::string message(msg,len);
    if ( isConnected()) {
        loop_->runInLoop(std::bind(&TcpConnection::sendInLoop,this,message));
    }
}

void TcpConnection::sendInLoop(const std::string& message)
{
    size_t len = message.size();
    const char* msg = message.data();
    ssize_t send_size = connSocket_.Send(msg, len);
    if (send_size < 0 ) {
        printErrorMsg("TcpConnection::sendInLoop");

    }else if(send_size < len){
        //将没有发送的数据写入发送缓冲区中
        writeBuf_.write(msg + send_size, len - send_size);
        //关注写事件
        if(!connChannel_.isWriting())
            connChannel_.enableWriting();
    }


}


void TcpConnection::handleClose()
{
    assert(connectState_ == kConnected);
    connectState_ = kdisConnected;
    //关闭对连接上所有事件的关注
    connChannel_.disenableAllEvent();
    //执行回调
    if(closeCallBack_)
        closeCallBack_(shared_from_this());
}
void TcpConnection::handleWrite()
{
    size_t readable = writeBuf_.readableBytes();
    ssize_t size = connSocket_.Send(writeBuf_.readBegin(), readable);
    if ( size < 0 ) {
        if(errorCallBack_) errorCallBack_();
        return;
    }
    writeBuf_.skip((size_t) size);
    //当写完缓冲区中所有的数据时 关闭写事件.
    if ( size == readable )
        connChannel_.disenableWriting();

}
void TcpConnection::destoryConn()
{
    connectState_ = kdisConnected;
    connChannel_.disenableAllEvent();
    connChannel_.removeSelf();
    connSocket_.closeFd();
}
void TcpConnection::shutdown()
{
    if(connectState_ == kConnected){
        connectState_ = kdisConnecting;
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop,this));
    }
}
void TcpConnection::shutdownInLoop()
{
    loop_->assertInLoopThread();
    //在没有可写的数据时,关闭写的一端
    if(!connChannel_.isWriting())
        connSocket_.shutDownWrite();
}

}//namespace net