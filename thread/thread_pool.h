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
    /*
     *@descriprion: 消费这生产者模型:
     *                  主线程生产出待消费的任务,子线程去执行
     *@param:线程池线程数量
     *
     */
    ThreadPool(size_t thread_num = kInitThreadNum)
            :threads_(thread_num, Thread(std::bind(&ThreadPool::threadTodo, this))), isRunning_(false)
    {

    }
    /*
     *@param: 线程要去执行的函数(threadFun) 线程池的线程数量
     *
     */
    ThreadPool(ThreadTask task, size_t thread_num = kInitThreadNum)
            :threads_(thread_num, Thread(task)), isRunning_(false)
    {
    }

    void threadTodo();
    /*
     *@descriprion: 添加任务
     */
    void appendTask(const ThreadTask& task);

    void appenTask(std::initializer_list<ThreadTask> tasks);

    /*
     *@descriprion: 调用run函数使线程池工作起来
     */
    void run()
    {
        isRunning_ = true;
        for (auto& thread : threads_)
            thread.run();

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

    void stopRunning()
    {
        isRunning_ = false;
    }

    ~ThreadPool()
    {
        join();
    }

private:
    bool isRunning_;
    Condition  emptyCond_;
    std::vector<Thread> threads_;
    MutexLock queueMutex_;
    std::queue<ThreadTask> taskQueue_;
};

#endif //BASE_NET_LIB_THREADPOOL_H
