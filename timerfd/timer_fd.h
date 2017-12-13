#ifndef _BASE_NET_LIB_TIMERFD_H_
#define _BASE_NET_LIB_TIMERFD_H_


#include <sys/timerfd.h>
#include <zconf.h>


namespace net {
class TimerFd  {
public:
    TimerFd();

    int getTimerFd()const
    {
        return fd_;
    }
    /* @descriprion: 设置定时器的超时时间
     * @param: 第一个参数为第一次timerfd触发的时间(从现在开始 单位:s)
     *         第二个参数为超时时间
     * @return: 设置成功或者失败
     */
    bool setTime(const int after_time, const int timeout);
private:
    int fd_;
};
}//namespace net

#endif//!_BASE_NET_LIB_TIMERFD_H_
