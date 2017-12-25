//
// Created by yangning on 17-12-19.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_THREADLOOPPOOL_H
#define BASE_NET_LIB_THREADLOOPPOOL_H

#include "thread_pool.h"
#include "../event_loop.h"
class ThreadLoopPool {
public:
    ThreadLoopPool(size_t thread_num = ThreadPool::kInitThreadNum)
            :threadPool_(thread_num)
    {
    }

    void threadFun()
    {
        net::EventLoop loop(net::POLL);
    }

    ~ThreadLoopPool()
    {
    }

private:
    ThreadPool threadPool_;
};

#endif //BASE_NET_LIB_THREADLOOPPOOL_H
