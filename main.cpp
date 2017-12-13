//
// Created by yangning on 17-12-13.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//


#include "event_loop.h"
#include "common.h"
#include "thread/Thread.h"
#include "timerfd/timer_fd.h"
#include "timerfd/time_stamp.h"
#include "channel.h"

int main()
{
    net::TimeStamp::printTimeNow();

    net::EventLoop loop(net::POLL);
    std::cout << "pid is " << getpid() << " main thread id is " << pthread_self() << " \n";
    net::TimerFd timerFd;
    timerFd.setTime(4,4);
    net::Channel channel(&loop,timerFd.getTimerFd());
    channel.setReadCallBack([&loop](){
      loop.quitLoop();
    });
    channel.enableReading();
    loop.startLoop();


    net::TimeStamp::printTimeNow();


    return 0;
}


