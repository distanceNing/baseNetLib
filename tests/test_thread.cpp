//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "thread/thread_pool.h"
#include "thread/Thread.h"
#include "thread/lock.h"

#include <iostream>
#include <sys/wait.h>
#include <zconf.h>
#include <vector>
using std::cout;
int g_value = 10;
int main()
{
    std::vector<Thread> threads(5,Thread());
    for (int i = 0; i < 5; ++i) {
        threads[i].setThreadFun([&i](){
          cout << "this is " << i << " thread\n";
          ++g_value;
          //sleep(1);
          //MutexLock lock(mutex);

          cout << "g_value = "<<g_value<<"\n";
        });
        threads[i].createThread();
    }
    for(auto & ite : threads)
    {
        ite.join();
    }
    return 0;
}