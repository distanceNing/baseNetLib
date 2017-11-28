#ifndef _BASE_NET_LIB_TIMERFD_H_
#define _BASE_NET_LIB_TIMERFD_H_


#include <sys/timerfd.h>
#include <zconf.h>


namespace net {
class TimerFd  {
public:
    TimerFd();

    bool setTime(const int after_time, const int timeout);
private:
    int fd_;
};
}//namespace net

#endif//!_BASE_NET_LIB_TIMERFD_H_
