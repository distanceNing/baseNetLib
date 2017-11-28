//
// Created by yangning on 17-10-23.
//

#include "timer_fd.h"
#include <cstring>

#include "../common.h"
#include "../event_loop.h"
namespace net {
TimerFd::TimerFd()

{
    fd_ = timerfd_create(CLOCK_REALTIME, 0);
    if (fd_ < 0) {
        printErrorMsg("create timer fd");
    }
}

bool TimerFd::setTime(const int after_time, const int timeout)
{
    struct itimerspec new_value;
    struct timespec now;
    if (clock_gettime(CLOCK_REALTIME, &now) == -1) {
        printErrorMsg("clock gettime");
    }
    memset(&new_value, 0, sizeof(new_value));
    new_value.it_value.tv_sec = now.tv_sec + after_time;
    new_value.it_value.tv_nsec = now.tv_nsec;

    new_value.it_interval.tv_sec = timeout;
    new_value.it_interval.tv_nsec = 0;

    if (timerfd_settime(fd_, TFD_TIMER_ABSTIME, &new_value, NULL) == -1) {
        printErrorMsg("timer fd settime");
    }
    return true;
}


}//namespace net

