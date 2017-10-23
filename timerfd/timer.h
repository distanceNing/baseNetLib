#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/timerfd.h>
#include <zconf.h>

class Timer
{
public:
    Timer(){}

    bool createTimer();

    bool setTime(const int after_time,const int timeout);

    int getTimerFd() const 
    {
        return time_fd_;
    }

    ~Timer()
    {
        close(time_fd_);
    }

private:
    int time_fd_;
};

void printTime();
#endif//!_TIMER_H_
