//
// Created by yangning on 17-10-25.
//

#ifndef BASE_NET_LIB_THREAD_H
#define BASE_NET_LIB_THREAD_H

#include <pthread.h>

class Thread {
public:
    Thread() { }

    static void* threadFun(void*);

    static pid_t getCurrentThreadID();

    void createThread();

    void join();

    void cancel();

    pthread_t getThreadID();

    virtual void run() = 0;

    ~Thread() { }

private:
    pthread_t threadID_;
};

#endif //BASE_NET_LIB_THREAD_H
