#include "event_loop.h"
#include "channel.h"
#include "timerfd/time_stamp.h"
#include <pthread.h>
namespace net {
bool EventLoop::isInLoopThread()
{
    return threadId_ == Thread::getCurrentThreadID();
}

void EventLoop::startLoop()
{
    assert(isInLoopThread());
    isLooping_ = true;
    while (isLooping_) {
        if (!activeChannels_.empty())
            activeChannels_.clear();

        TimeStamp time = poller_->Poll(kTimeOut, activeChannels_);
        //time.printTime();
        //处理socket上发生的事件
        handleEvent();
        doTaskInQueue();
    }
}

void EventLoop::addNewChannel(Channel* channel)
{
    assert(channel != NULL);
    poller_->addNewChannel(channel);
}

void EventLoop::handleEvent()
{
    if (activeChannels_.empty())
        return;
    for (auto i : activeChannels_) {
        i->handleEvent();
    }
}
void EventLoop::removeChannel(Channel* channel)
{
    assert(channel != NULL);
    poller_->removeChannel(channel);
}
void EventLoop::updateChannel(Channel* channel)
{
    assert(this == channel->getOwnLoop());
    poller_->updateChannel(channel);
}
} //namespace net
