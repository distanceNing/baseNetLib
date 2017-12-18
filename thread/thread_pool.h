//
// Created by yangning on 17-10-25.
//
// Descriprion :thread pool
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_THREADPOOL_H
#define BASE_NET_LIB_THREADPOOL_H

#include <vector>
#include <queue>
#include <initializer_list>
#include <iostream>
#include "Thread.h"
#include "lock.h"

class ThreadPool {
public:
    using ThreadTask = std::function<void()>;
    static const size_t kInitThreadNum = 4;
    ThreadPool(size_t thread_num = kInitThreadNum)
            :threads_(thread_num, Thread(std::bind(&ThreadPool::threadTodo, this))),isrunning_(false)
    {

    }

    void threadTodo()
    {
        std::cout<<Thread::getCurrentThreadID()<<" is running ---\n";
        while (isrunning_) {
            if ( !taskQueue_.empty()) {
                ThreadTask task;
                {
                    MutexRAII raii(queueMutex_);
                    task = std::move(taskQueue_.front());
                    taskQueue_.pop();
                }
                std::cout<<Thread::getCurrentThreadID()<<" i get a task ---\n";
                task();
            }
        }
    }

    void appendTask(const ThreadTask& task)
    {
        MutexRAII raii(queueMutex_);
        taskQueue_.push(task);
    }

    void appenTask(std::initializer_list<ThreadTask> tasks)
    {
        MutexRAII raii(queueMutex_);
        for(auto& task : tasks )
            taskQueue_.push(task);
    }
    void run()
    {
        isrunning_ = true ;
        for (auto& thread : threads_)
            thread.run();


    }

    void cancel()
    {
        for (auto& thread :threads_)
            thread.cancel();
    }

    void join()
    {
        for (auto& thread :threads_)
            thread.join();
    }

    bool taskQueueIsEmpty() const
    {
        return taskQueue_.empty();
    }

    bool stopRunning()
    {
        isrunning_=false;
    }

    ~ThreadPool()
    {
        join();
    }

private:
    bool isrunning_;
    std::vector<Thread> threads_;
    MutexLock queueMutex_;
    std::queue<ThreadTask> taskQueue_;
};

#endif //BASE_NET_LIB_THREADPOOL_H
