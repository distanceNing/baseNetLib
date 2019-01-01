//
// Created by yangning on 17-10-25.
//

//#include <zconf.h>
#include "Thread.h"
#include <pthread.h>

void* Thread::threadFun(void* arg)
{
    Thread* thread= static_cast<Thread*>(arg);
    thread->threadFun_();
    return NULL;
}

void Thread::join()
{
    pthread_join(threadID_,NULL);
}

pthread_t Thread::getThreadID()
{
    return threadID_;
}

pthread_t Thread::getCurrentThreadID()
{
    return pthread_self();
}

