#ifndef BASE_NET_LIB_POLL_POLLER_H
#define BASE_NET_LIB_POLL_POLLER_H
#include <sys/types.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>


#include <vector>
#include <map>


#include "../common.h"
#include "poller.h"

#include "../timerfd/time_stamp.h"

namespace net {
class PollPoller : public Poller {

public:
    PollPoller()
    {
    }

    TimeStamp Poll(int time_out, ChannelList& activeChannel) override;

    void addNewChannel(Channel* channel) override;

    void removeChannel(Channel* channel) override;

    ~PollPoller()
    {
    }

private:
    void fillActiveChannel(int num_ready, ChannelList& activeChannel);
    std::vector<struct pollfd> pollfdList_;
};
}// namespace net
#endif//!BASE_NET_LIB_POLL_POLLER_H
