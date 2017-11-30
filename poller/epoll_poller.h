//
// Created by yangning on 17-10-23.
//

#ifndef BASE_NET_LIB_EPOLL_POLLER_H
#define BASE_NET_LIB_EPOLL_POLLER_H
#include "poller.h"
#include <sys/epoll.h>
#include <vector>
namespace net {
class EpollPoller : public Poller {
public:

    EpollPoller();

    TimeStamp Poll(int time_out, ChannelList& activeChannel) override;

    void addNewChannel(Channel* channel) override;

    void removeChannel(Channel* channel) override;

    ~EpollPoller()
    {
    }
protected:

    const uint32_t kEPOLL_MODE = 1;

    using EpollEventList=std::vector<struct epoll_event>;

private:
    const unsigned long kInitEpollEventSize = 16;

    void fillActiveChannel(int num_ready, ChannelList& activeChannel);

    int epollFd_;

    EpollEventList epollEventList_;
};
}//namespace net
#endif //BASE_NET_LIB_EPOLL_POLLER_H
