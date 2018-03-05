//
// Created by yangning on 17-12-15.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_SORTTIMERLIST_H
#define BASE_NET_LIB_SORTTIMERLIST_H
#include "../common.h"
#include "time_stamp.h"
#include <functional>
#include <list>
#include <algorithm>
struct Timer{
    using TimerCallBack= std::function<void()>;
    
    int64_t exptime_;
    TimerCallBack timerCallBack_;   
    void setTimerCallBack(const TimerCallBack& timerCallBack){
        timerCallBack_ = timerCallBack;
    }
    
};
/*
 * 定时器链表,它是一个按超时时间排序的升序链表. 
 * 
 */
class SortTimerList {
public:
    using TimerList =std::list<const struct Timer*>;
    SortTimerList()
    {
    }
    bool empty()
    {
        return timerList_.empty();
    }
    
    void addTimer(const struct Timer* timer);

    void adjustTimer(const struct Timer* timer);

    void deleteTimer(const struct Timer* timer);

    void process();

    ~SortTimerList()
    {
    }

private:
    void addTimer(const struct Timer* timer,TimerList::iterator ite)
    {
        auto temp=std::find_if(ite,timerList_.end(),[&ite](TimerList::value_type& temp_ite){
          return (*ite)->exptime_ < temp_ite->exptime_;
        });
        timerList_.insert(temp,timer);
    }

    TimerList timerList_;
};

#endif //BASE_NET_LIB_SORTTIMERLIST_H
