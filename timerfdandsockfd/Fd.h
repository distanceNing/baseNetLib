//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_FD_H
#define BASE_NET_LIB_FD_H

#include <poll.h>
#include <functional>
namespace net {
class EventLoop;
}
namespace net{
class Fd {

public:
    using EventCallBack = std::function<void()>;

    Fd(EventLoop* own_loop)
            :ownEventLoop_(own_loop), fd_(-1), events_(-1), revents_(-1),
             readCallBack_(NULL), writeCallBack_(NULL),errorCallBack_(NULL)
    { }

    void setWriteCallBack(EventCallBack call_back);

    void setReadCallBack(EventCallBack call_back);

    void setErrorCallBack(EventCallBack call_back);

    void setEvents(int events);

    void setRetEvents(int ret_events);

    void resetFd(int fd);

    short getEvents() const;

    int getFd() const;

    void closeFd();

    void handleEvent();

    void removeSelf() ;

    virtual ~Fd() { closeFd();}

protected:
    EventLoop* ownEventLoop_;
    int fd_;
    short events_;
    short revents_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;
};
}//namespace net
#endif //BASE_NET_LIB_FD_H
