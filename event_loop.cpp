#include "event_loop.h"


bool EventLoop::isLoopInThisThread()
{
    return threadId_==getpid();
}


void EventLoop::startLoop()
{
    isLooping_=true;
    while(isLooping_)
    {
        if(!activeChannels_.empty())
            activeChannels_.clear();
        poller_->Poll(kTimeOut,activeChannels_);
        handleEvent();
    }
}

void EventLoop::addNewChannel(Channel* channel)
{
    if(channel != NULL)
        poller_->addNewChannel(channel);
}


void EventLoop::handleEvent()
{
    if(activeChannels_.empty())
        return;
    for(auto i : activeChannels_)
    {
        i->handleEvent();
    }
}
