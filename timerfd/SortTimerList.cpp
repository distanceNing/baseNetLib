//
// Created by yangning on 17-12-15.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "SortTimerList.h"
void SortTimerList::process()
{
    if(timerList_.empty())
        return;
    int64_t cur_time=net::TimeStamp::nowTime();

    for(auto ite =timerList_.begin() ;ite !=timerList_.end();)
    {
        if((*ite)->exptime_ > cur_time)
            break;
        (*ite)->timerCallBack_();
        timerList_.erase(ite++);
    }
}
void SortTimerList::deleteTimer(const struct Timer* timer)
{
    timerList_.remove(timer);
}
void SortTimerList::addTimer(const struct Timer* timer)
{
    if(timerList_.empty()||timer->exptime_ > timerList_.back()->exptime_)
    {
        timerList_.push_back(timer);
        return;
    }
    if(timer->exptime_ < timerList_.front()->exptime_)
    {
        timerList_.push_front(timer);
        return;
    }
    addTimer(timer,timerList_.begin());
}
void SortTimerList::adjustTimer(const struct Timer* timer)
{
    auto ite=std::find(timerList_.begin(),timerList_.end(),timer);
    auto next_ite=ite;
    ++next_ite;
    /*
     * 当这个定时器在链表最后一个或它的超时时间还是小于下一个定时器,不用调整.
     */
    if(next_ite == timerList_.end() || timer->exptime_ < (*next_ite)->exptime_ )
        return;
    if(timer==timerList_.front())
    {
        timerList_.erase(timerList_.begin());
        addTimer(timer,timerList_.begin());
    }
    else
    {
        timerList_.erase(ite);
        addTimer(timer,next_ite);
    }
}
