//
// Created by yangning on 17-10-25.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "thread_pool.h"
void ThreadPool::threadTodo()
{
    std::cout << Thread::getCurrentThreadID() << " is running ---\n";
    while (isRunning_) {
        if (taskQueueIsEmpty()){
            emptyCond_.wait();
        }
         //获取任务队列mutex
        MutexRAII raii(queueMutex_);
        if(!isRunning_ && taskQueueIsEmpty())
            return;
        ThreadTask task;
        {
            task = std::move(taskQueue_.front());
            taskQueue_.pop();
        }
        std::cout << Thread::getCurrentThreadID() << " i get a task ---\n";
        task();
    }
}

void ThreadPool::appenTask(std::initializer_list<ThreadPool::ThreadTask> tasks)
{
    MutexRAII raii(queueMutex_);
    emptyCond_.signal();
    for (auto& task : tasks)
        taskQueue_.push(task);
}
void ThreadPool::appendTask(const ThreadPool::ThreadTask& task)
{
    MutexRAII raii(queueMutex_);
    if ( !isRunning_ )
    {
        std::cout<<"the thread pool is stop \n";
        return;
    }
    taskQueue_.push(task);
    emptyCond_.signal();
}
