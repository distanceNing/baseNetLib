//
// Created by yangning on 17-11-27.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_MUTEXLOCK_H
#define BASE_NET_LIB_MUTEXLOCK_H
#include <mutex>
#include <pthread.h>
class MutexLock {
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex_, NULL);
    }
    inline void lock()
    {
        pthread_mutex_lock(&mutex_);
    }

    inline void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }
    ~MutexLock()
    {
        unlock();
        pthread_mutex_destroy(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
};

//条件变量用于线程之间同步共享数据的值,条件变量提供了一种线程间的通知机制当某个共享数据到达某个值的时候,唤醒
//等待这个共享数据的线程

class Cond {
public:
    Cond()
    {
        if (!pthread_mutex_init(&mutex_, NULL))
            perror("pthread_mutex_init");
        if (!pthread_cond_init(&cond_, NULL)) {
            pthread_mutex_destroy(&mutex_);
            perror("pthread_cond_init");
        }
    }

    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock(&mutex_);
        ret = pthread_cond_wait(&cond_, &mutex_);
        pthread_mutex_unlock(&mutex_);
        return ret == 0;
    }

    bool signal()
    {
        return 0==pthread_cond_signal(&cond_);
    }

    virtual ~Cond()
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&cond_);
    }

private:
    pthread_cond_t cond_;
    pthread_mutex_t mutex_;
};

#endif //BASE_NET_LIB_MUTEXLOCK_H
