//
// Created by yangning on 17-10-25.
//

#ifndef BASE_NET_LIB_THREAD_H
#define BASE_NET_LIB_THREAD_H

#include <pthread.h>
#include <functional>
class Thread {
public:
    using ThreadFun =std::function<void()>;
    Thread(const ThreadFun& thread_fun ):threadFun_(thread_fun) { }

    Thread(){}

    static void* threadFun(void*);

    static pid_t getCurrentThreadID();

    void createThread();

    void setThreadFun(const ThreadFun& thread_fun){
        threadFun_=thread_fun;
    }

    void join();

    void cancel();

    void run()
    {
        threadFun_();
    }

    pthread_t getThreadID();

    ~Thread() { }

private:
    pthread_t threadID_;
    ThreadFun threadFun_;
};

#endif //BASE_NET_LIB_THREAD_H
