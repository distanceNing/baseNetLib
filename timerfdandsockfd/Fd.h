//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_FD_H
#define BASE_NET_LIB_FD_H

#include <poll.h>

class Fd{
protected:
    typedef void (* EventCallBack)(void *);
public:
    Fd() { }

    void setWriteCallBack(EventCallBack call_back);

    void setReadCallBack(EventCallBack call_back);

    void setErrorCallBack(EventCallBack call_back);

    void setEvents(int events);

    void setRetEvents(int ret_events);

    short getEvents() const;

    int getFd() const;

    virtual void handleEvent() = 0;

    virtual ~Fd() { }

protected:
    int fd_;
    short events_;
    short revents_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;
};

#endif //BASE_NET_LIB_FD_H
