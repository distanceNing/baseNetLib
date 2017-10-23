//
// Created by yangning on 17-10-23.
//

#ifndef POLLER_EPOLL_POLLER_H
#define POLLER_EPOLL_POLLER_H
#include "poller.h"
#include <sys/epoll.h>
#include <vector>
class EpollPoller: public Poller
{
public:

    EpollPoller();

    int Poll(int time_out,ChannelList & activeChannel) override;

    void addNewChannel(Channel * channel) override ;

    void removeChannel(Channel * channel) override;

    ~EpollPoller(){}
protected:
    using EpollEventList=std::vector<struct epoll_event> ;
private:
    const int kInitEpollEventSize = 16;

    void fillActiveChannel(int num_ready,ChannelList &activeChannel);

    int epollFd_;

    EpollEventList epollEventList_;
};

#endif //POLLER_EPOLL_POLLER_H
