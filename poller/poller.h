//
// Created by yangning on 17-10-23.
//

#ifndef BASE_NET_LIB_POLLER_H
#define BASE_NET_LIB_POLLER_H
#include "../timerfdandsockfd/Fd.h"
#include <map>
#include <vector>
#include "../timerfdandsockfd/time_stamp.h"

namespace net {
class Poller {

protected:
    typedef std::vector<Fd*> ChannelList;
    typedef std::map<int, Fd*> ChannelMap;

public:
    Poller()
    {
    }

    virtual TimeStamp Poll(int time_out, ChannelList& activeChannel) = 0;

    virtual void addNewChannel(Fd* channel) = 0;

    virtual void removeChannel(Fd* channel) = 0;

protected:
    ChannelMap channelMap_;

};
} //namespace net
#endif //BASE_NET_LIB_POLLER_H
