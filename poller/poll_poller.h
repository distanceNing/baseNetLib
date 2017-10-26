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

#include "../timerfdandsockfd/Fd.h"
#include "../common.h"
#include "poller.h"
#include "../timerfdandsockfd/time_stamp.h"

class PollPoller:public Poller
{

public:
    PollPoller() { }

    TimeStamp Poll(int time_out,ChannelList & activeChannel) override;

    void addNewChannel(Fd * channel) override ;

    void removeChannel(Fd * channel) override;

    ~PollPoller(){}

private:
    void fillActiveChannel(int num_ready,ChannelList &activeChannel);
    std::vector<struct pollfd> pollfdList_;
};

#endif//!BASE_NET_LIB_POLL_POLLER_H
