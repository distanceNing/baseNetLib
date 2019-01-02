//
// Created by yangning on 17-12-19.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
namespace  net{
//轮盘法分配连接
EventLoop* EventLoopThreadPool::getNextLoop()
{

    EventLoop* ioloop = loops_.empty() ? serverLoop_ : threads_[currentConnNum_%loops_.size()].getEventLoop();
    currentConnNum_++;
    return ioloop;
}
EventLoopThreadPool::EventLoopThreadPool(EventLoop* loop, size_t thread_num)
        :serverLoop_(loop),threads_(thread_num),currentConnNum_(0)
{
    for(auto& thread: threads_)
        thread.run();

}
EventLoopThreadPool::~EventLoopThreadPool()
{
}
}//namespace net
