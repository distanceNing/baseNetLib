#ifndef _BASE_NET_LIB_TIMER_H_
#define _BASE_NET_LIB_TIMER_H_

#include "Fd.h"
#include <sys/timerfd.h>
#include <zconf.h>

class Timer:public Fd
{
public:
    Timer();

    void handleEvent() override ;

    bool setTime(const int after_time,const int timeout);

    virtual ~Timer()
    {
        close(fd_);
    }

};


#endif//!_BASE_NET_LIB_TIMER_H_
