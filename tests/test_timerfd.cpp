#include "event_loop.h"
#include "timerfdandsockfd/timer_fd.h"
#include "common.h"
#include "timerfdandsockfd/time_stamp.h"


EventLoop* g_loop;


void timeRCB(void* arg)
{
    TimerFd* fd = static_cast<TimerFd*>(arg);
    int64_t error;
    error = 0;
    ssize_t size;
    size =  read(fd->getFd(), &error, sizeof(error));
    printf("timeRCB read  size is : %lu\n", size);
    g_loop->quitLoop();
}

int main()
{
    TimeStamp::printTimeNow();


    EventLoop main_loop(EPOLL);

    TimerFd timer;
    //第一个参数为第一次timerfd触发的时间(从现在开始 单位:s)
    timer.setTime(4, 4);
    timer.setEvents(POLLIN);
    timer.setReadCallBack(timeRCB);
    main_loop.addNewChannel(&timer);
    g_loop = &main_loop;
    main_loop.startLoop();

    TimeStamp::printTimeNow();
    return 0;
}
