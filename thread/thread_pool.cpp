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
        if ( !taskQueue_.empty()) {
            ThreadTask task;
            {
                MutexRAII raii(queueMutex_);
                task = std::move(taskQueue_.front());
                taskQueue_.pop();
            }
            std::cout << Thread::getCurrentThreadID() << " i get a task ---\n";
            task();
        }
    }
}
void ThreadPool::appenTask(std::initializer_list<ThreadPool::ThreadTask> tasks)
{
    MutexRAII raii(queueMutex_);
    for (auto& task : tasks)
        taskQueue_.push(task);
}
void ThreadPool::appendTask(const ThreadPool::ThreadTask& task)
{
    MutexRAII raii(queueMutex_);
    taskQueue_.push(task);
}
