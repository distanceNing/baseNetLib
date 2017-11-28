//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_CHANNEL_H
#define BASE_NET_LIB_CHANNEL_H

#include <functional>
#include <zconf.h>
#include "event_loop.h"

namespace net {
using EventCallBack=std::function<void()>;
class Channel {
public:
    Channel(EventLoop* ownEventLoop_, const int fd_)
            :ownEventLoop_(ownEventLoop_), fd_(fd_), events_(0), revents_(0)
    {
    }

    void setWriteCallBack(EventCallBack call_back)
    {
        writeCallBack_ = call_back;
    }

    void setReadCallBack(EventCallBack call_back)
    {
        readCallBack_ = call_back;
    }

    void setErrorCallBack(EventCallBack call_back)
    {
        errorCallBack_ = call_back;
    }

    void setEvents(int events)
    {
        events_ = static_cast<short >(events);
    }

    void setRetEvents(int ret_events)
    {
        revents_ = static_cast<short >(ret_events);
    }

    short getEvents() const
    {
        return events_;
    }

    int getFd() const
    {
        return fd_;
    }

    void closeFd()
    {
        close(fd_);
    }

    void handleEvent();

    void removeSelf()
    {
        ownEventLoop_->removeChannel(this);
    }

    ~Channel()
    {
    }

private:
    EventLoop* ownEventLoop_;
    const int fd_;
    short events_;
    short revents_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;

};
}// namespace net
#endif //BASE_NET_LIB_CHANNEL_H
