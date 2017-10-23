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

#include "../channel.h"
#include "../common.h"
#include "poller.h"

class PollPoller:public Poller
{

public:
    PollPoller()
    {
    }

    int Poll(int time_out,ChannelList & activeChannel) override;

    void addNewChannel(Channel * channel) override ;

    void removeChannel(Channel * channel) override;

    ~PollPoller(){}

private:
    void fillActiveChannel(int num_ready,ChannelList &activeChannel);
    std::vector<struct pollfd> pollfdList_;
};

#endif//!BASE_NET_LIB_POLL_POLLER_H
