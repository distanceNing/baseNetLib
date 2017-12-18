#include <iostream>
#include <zconf.h>
#include "thread/thread_pool.h"



int main()
{

    ThreadPool threadPool;

    threadPool.run();

    ThreadPool::ThreadTask task=[](){
      std::cout<<"thread id is : "<<Thread::getCurrentThreadID()<<std::endl;
      sleep(1);
    };
    for(int i = 0 ; i< 10;++i)
        threadPool.appendTask(task);


    sleep(2);
    threadPool.stopRunning();

    return 0;
}