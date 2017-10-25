#ifndef _BASE_NET_LIB_TIMERFD_H_
#define _BASE_NET_LIB_TIMERFD_H_

#include "Fd.h"
#include <sys/timerfd.h>
#include <zconf.h>

class TimerFd:public Fd
{
public:
    TimerFd(EventLoop* own_loop);

    void handleEvent() override ;

    void removeSelf() override;

    bool setTime(const int after_time,const int timeout);

    virtual ~TimerFd()
    {
        close(fd_);
    }

};


#endif//!_BASE_NET_LIB_TIMERFD_H_
