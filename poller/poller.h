//
// Created by yangning on 17-10-23.
//

#ifndef BASE_NET_LIB_POLLER_H
#define BASE_NET_LIB_POLLER_H
#include "../channel.h"
#include <map>
#include <vector>

class Poller {

protected:

    typedef std::map<int,Channel*> ChannelMap;
    typedef std::vector<Channel*> ChannelList;

public:

    virtual int Poll(int time_out,ChannelList & activeChannel) = 0;

    virtual void addNewChannel(Channel * channel) = 0;

    virtual void removeChannel(Channel * channel) = 0;

protected:
    ChannelMap channelMap_;

};

#endif //BASE_NET_LIB_POLLER_H
