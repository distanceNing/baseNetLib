//
// Created by yangning on 17-12-19.
//
// Descriprion :tcpserver用一个事件循环来专门接受连接,在新建一个TCPConnection的时候,从EventLoopPool中挑选出一个loop给conn用
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_THREADLOOPPOOL_H
#define BASE_NET_LIB_THREADLOOPPOOL_H


#include <vector>
#include <cstring>
namespace net{
class EventLoopThread;
class EventLoop;


class EventLoopThreadPool {
public:
    EventLoopThreadPool(EventLoop* loop,size_t thread_num = 0);


    EventLoop* getNextLoop();

    ~EventLoopThreadPool();

private:
    EventLoop* serverLoop_;
    std::vector<EventLoopThread> threads_;
    std::vector<EventLoop*> loops_;
    size_t currentConnNum_;
};
}//namespace net

#endif //BASE_NET_LIB_THREADLOOPPOOL_H
