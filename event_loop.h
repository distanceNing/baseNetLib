//
// Created by yangning on 17-10-24.
//
// Descriprion :事件循环每个线程只能存在一个loop.
//
// Copyright (c) yangning All rights reserved.
//
#ifndef BASE_NET_LIB_EVENTLOOP_H
#define BASE_NET_LIB_EVENTLOOP_H

#include <vector>
#include <memory>

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "poller/poll_poller.h"
#include "poller/epoll_poller.h"
#include "thread/Thread.h"
namespace net{
class Channel;
}
namespace net {
const int kTimeOut = 10 * 1000;

enum POLL_TYPE {
  POLL = 0, EPOLL,
};

inline Poller* createPoller(POLL_TYPE pollType)
{
    if (pollType == POLL)
        return new PollPoller;
    return new EpollPoller;
}

class EventLoop : boost::noncopyable{
protected:
    typedef std::vector<Channel*> ChannelList;
public:
    EventLoop(POLL_TYPE pollType)
            :isLooping_(false), threadId_(Thread::getCurrentThreadID()), poller_(createPoller(pollType))
    {
    }

    ~EventLoop()
    {
    }
    void runInLoop( ){
        if(isInLoopThread())
        {

        }
    }

    bool isInLoopThread();

    void updateChannel(Channel* channel);

    void startLoop();

    void quitLoop()
    {
        isLooping_ = false;
    }

    void handleEvent();

    void addNewChannel(Channel* channel);

    void removeChannel(Channel* channel);

private:
    bool isLooping_;
    const pthread_t threadId_;
    ChannelList activeChannels_;
    boost::scoped_ptr<Poller> poller_;

};
} //namespace net
#endif//!BASE_NET_LIB_EVENTLOOP_H
