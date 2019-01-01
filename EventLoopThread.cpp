//
// Created by yangning on 18-3-13.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "EventLoopThread.h"
#include "event_loop.h"

void net::EventLoopThread::threadFun()
{
    loop_ = new EventLoop(POLL);
    loop_->startLoop();
}
net::EventLoopThread::EventLoopThread()
        :thread_(std::bind(&EventLoopThread::threadFun,this)),loop_(nullptr)
{
}

net::EventLoopThread::~EventLoopThread()
{
    if(loop_)
        delete( loop_);
}
