//
// Created by yangning on 17-11-27.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "lock.h"
MutexRAII::MutexRAII(MutexLock& mutexLock_)
        :mutexLock_(mutexLock_)
{
    mutexLock_.lock();
}
MutexRAII::~MutexRAII()
{
    mutexLock_.unlock();
}
