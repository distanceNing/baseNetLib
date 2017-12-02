//
// Created by yangning on 17-10-25.
//

#include <zconf.h>
#include "Thread.h"
#include <pthread.h>

void* Thread::threadFun(void* arg)
{
    Thread* thread= static_cast<Thread*>(arg);
    thread->run();
    return NULL;
}

void Thread::createThread()
{
    pthread_create(&threadID_,NULL,threadFun,this);
}

void Thread::join()
{
    pthread_join(threadID_,NULL);
}

void Thread::cancel()
{
    pthread_cancel(threadID_);
}
pthread_t Thread::getThreadID()
{
    return threadID_;
}
pid_t Thread::getCurrentThreadID()
{
    return getpid();
}

