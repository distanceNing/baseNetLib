//
// Created by yangning on 17-11-28.
//
// Descriprion :事件处理器,用于事件处理.通过添加回调函数,在fd上发生事件时,调用相应的回调函数.
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_CHANNEL_H
#define BASE_NET_LIB_CHANNEL_H

#include <functional>
#include <zconf.h>
#include <cassert>
#include <sys/poll.h>

namespace net {
class EventLoop;
using EventCallBack=std::function<void()>;
class Channel {
public:
    static const int kNonWrite = ~POLLOUT;
    static const int kNonRead = ~POLLIN;
    static const int kNonEvent = 0;
    static const int kWrite = POLLOUT;
    static const int kRead = POLLIN;
    static const int kError = POLLERR;

    Channel(EventLoop* ownEventLoop_, const int fd_);

    const net::EventLoop* getOwnLoop() const
    {
        return ownEventLoop_;
    }

    void disenableAllEvent();
public:
    bool isWriting(){
        return (events_ & kWrite) != 0;
    }

    void setCloseCallBack(const EventCallBack& closeCallBack_);

    void setWriteCallBack(const EventCallBack& call_back)
    {
        writeCallBack_ = call_back;
    }

    void setReadCallBack(const EventCallBack& call_back)
    {
        readCallBack_ = call_back;
    }

    void setErrorCallBack(const EventCallBack& call_back)
    {
        errorCallBack_ = call_back;
    }

    void enableReading();

    void disenableReading();

    void enableWriting();

    void disenableWriting();

    void enableError();

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

    void handleEvent();

    void removeSelf();

public:
    void setIsAddInLoop(bool isAddInLoop_);
    ~Channel()
    {
        assert(!eventHandling_);
    }

private:
    EventLoop* ownEventLoop_;
    bool isAddInLoop_;
    bool eventHandling_;
private:
    const int fd_;
    short events_;
    short revents_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;
    EventCallBack closeCallBack_;


};
}// namespace net
#endif //BASE_NET_LIB_CHANNEL_H
