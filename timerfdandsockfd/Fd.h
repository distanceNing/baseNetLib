//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_FD_H
#define BASE_NET_LIB_FD_H

#include <poll.h>


class EventLoop;

class Fd{

public:
    Fd(EventLoop* own_loop):ownEventLoop_(own_loop),fd_(-1),events_(-1),revents_(-1) { }

    typedef void (* EventCallBack)(void *);

    void setWriteCallBack(EventCallBack call_back);

    void setReadCallBack(EventCallBack call_back,void* arg);

    void setErrorCallBack(EventCallBack call_back);

    void setEvents(int events);

    void setRetEvents(int ret_events);

    void resetFd(int fd);

    short getEvents() const;

    int getFd() const;

    void closeFd();

    virtual void handleEvent() = 0;

    virtual void removeSelf() = 0;

    virtual ~Fd() { }

protected:
    EventLoop* ownEventLoop_;
    int fd_;
    short events_;
    short revents_;
    void* callBackArg_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;
};

#endif //BASE_NET_LIB_FD_H
