//
// Created by yangning on 17-10-23.
//
// Descriprion :负责I/O复用,事件分发.Poller为基类
//              poll和epoll两种不同的实现.
//
// Copyright (c) yangning All rights reserved.
//
#ifndef BASE_NET_LIB_POLLER_H
#define BASE_NET_LIB_POLLER_H

#include <map>
#include <vector>

#include "../timerfd/time_stamp.h"

namespace net {
class Channel;
}
namespace net {
class Poller {

protected:
    typedef std::vector<Channel*> ChannelList;
    typedef std::map<int, Channel*> ChannelMap;

public:
    Poller()
    {
    }

    virtual TimeStamp Poll(int time_out, ChannelList& activeChannel) = 0;

    virtual void addNewChannel(Channel* channel) = 0;

    virtual void removeChannel(Channel* channel) = 0;

    virtual void updateChannel(Channel* channel)
    {
    }
protected:
    ChannelMap channelMap_;

};

} //namespace net
#endif //BASE_NET_LIB_POLLER_H
