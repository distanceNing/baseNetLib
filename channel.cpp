//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include <poll.h>
#include <iostream>
#include "channel.h"
namespace net {
void Channel::handleEvent()
{
/*
 *
 * 这里有一个大坑:
 *  使用valgrind:
 *              Invalid read of size 2
 *               ==125733==    at 0x40D0C0: net::Channel::handleEvent() (channel.cpp:22) ~~
 *      在readcallback中可能对方关闭套接字导致read_size= 0 ,关闭连接.
 *      此时tcpconnection会析构掉这个connChannel,但是这个handleevent程序没有执行完毕,会导致内存访问越界.
 *
 */
    eventHandling_ = true;
    assert(isAddInLoop_);
    if ( revents_ & POLLHUP && !(revents_ & POLLIN)) {
        //std::cout << "fd " << fd_ << "  is POLLHUP ---" << std::endl;
        if ( closeCallBack_ )
            closeCallBack_();
    }

    if ( revents_ & POLLIN ) {
        // std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        if ( readCallBack_ )
            readCallBack_();
    }
    if ( revents_ & POLLOUT ) {
        if ( writeCallBack_ )
            writeCallBack_();
    }
    if ( revents_ & POLLERR ) {
        if ( errorCallBack_ )
            errorCallBack_();
    }
    eventHandling_ = false;
}

void Channel::setIsAddInLoop(bool isAddInLoop)
{
    this->isAddInLoop_ = isAddInLoop;
}
void Channel::setCloseCallBack(const EventCallBack& closeCallBack)
{
    Channel::closeCallBack_ = closeCallBack;
}
}//namespace net

