//
// Created by yangning on 17-10-24.
//

#ifndef BASE_NET_LIB_EVENTLOOP_H
#define BASE_NET_LIB_EVENTLOOP_H

#include <vector>
#include <memory>

#include <boost/scoped_ptr.hpp>


#include "poller/poll_poller.h"
#include "poller/epoll_poller.h"

class Fd;
const int kTimeOut = 10*1000;

enum POLL_TYPE
{
  POLL=0,
  EPOLL,
};

inline  Poller* createPoller(POLL_TYPE pollType)
{
    if(pollType==POLL)
        return new PollPoller;
    return new EpollPoller;
}

class EventLoop {

public:
    EventLoop(POLL_TYPE pollType)
            :isLooping_(false), threadId_(getpid()), poller_(createPoller(pollType)) { }

    ~EventLoop() { }

    bool isLoopInThisThread();

    void startLoop();

    void quitLoop()
    {
        isLooping_ = false;
    }

    void handleEvent();

    void addNewChannel(Fd* channel);

    void removeChannel(Fd* channel);
protected:
    typedef std::vector<Fd*> ChannelList;
private:
    bool isLooping_;
    const pid_t threadId_;
    ChannelList activeChannels_;
    boost::scoped_ptr<Poller> poller_;
};
#endif//!BASE_NET_LIB_EVENTLOOP_H
