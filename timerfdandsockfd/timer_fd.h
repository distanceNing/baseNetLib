#ifndef _BASE_NET_LIB_TIMERFD_H_
#define _BASE_NET_LIB_TIMERFD_H_

#include "Fd.h"
#include <sys/timerfd.h>
#include <zconf.h>
namespace net {
class TimerFd : public Fd {
public:
    TimerFd(EventLoop* own_loop);

    bool setTime(const int after_time, const int timeout);

};
}//namespace net

#endif//!_BASE_NET_LIB_TIMERFD_H_
