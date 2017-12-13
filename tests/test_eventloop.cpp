//
// Created by yangning on 17-10-25.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "common.h"
#include "thread/Thread.h"

net::EventLoop* g_loop;

int main()
{
    net::EventLoop loop(net::POLL);
    std::cout << "pid is " << getpid() << " main thread id is " << pthread_self() << " \n";
    g_loop = &loop;
    /*
     * 两个线程 两个事件循环
     * Thread thread(std::bind([]() {
      std::cout << "pid is " << getpid() << " thread id is " << pthread_self() << " \n";
      net::EventLoop child_thread_loop(net::POLL);
      child_thread_loop.startLoop();
    }));
    */

    //负面测试
    Thread thread(std::bind([]() {
        std::cout << "pid is " << getpid() << " thread id is " << pthread_self() << " \n";
        g_loop->startLoop();
    }));

    thread.run();
    loop.startLoop();


    //pthread_exit(NULL);

    return 0;
}

