//
// Created by yangning on 18-3-13.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_EVENTLOOPTHREAD_H
#define BASE_NET_LIB_EVENTLOOPTHREAD_H

#include <functional>
#include "thread/Thread.h"
namespace net{
class EventLoop;


class EventLoopThread {
public:
    EventLoopThread();

    void threadFun();

    void run(){
        thread_.run();
    }
    EventLoop* getEventLoop() const{
        return loop_;
    }

    ~EventLoopThread()
    {
        if(loop_)
            delete( loop_);
    }

private:
    Thread thread_;
    EventLoop* loop_;

};
}//namespace net
#endif //BASE_NET_LIB_EVENTLOOPTHREAD_H
