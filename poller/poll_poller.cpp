#include "poll_poller.h"

#include <stdlib.h>
#include <iostream>

TimeStamp PollPoller::Poll(int time_out, ChannelList& activeChannels)
{
    int num_ready = -1;
    std::cout << "Poll Array Size " << pollfdList_.size() << std::endl;

    num_ready = ::poll(pollfdList_.data(), pollfdList_.size(), time_out);
    TimeStamp timeStamp = TimeStamp();
    if (num_ready > 0)
    {
        std::cout << "Ready Event Num " << num_ready << std::endl;
        fillActiveChannel(num_ready, activeChannels);
    }
    else
    {
        if (num_ready == 0)
        {
            std::cout << "No Event Happened-----" << std::endl;
        }
        else
        {
            perror("Poll Error");
        }
    }
    return timeStamp;
}

void PollPoller::fillActiveChannel(int num_ready, ChannelList& activeChannels)
{
    for (std::vector<struct pollfd>::iterator i = pollfdList_.begin(); i!=pollfdList_.end(); ++i)
    {
        if (i->revents>0)
        {
            channelMap_[i->fd]->serRetEvents(i->revents);
            activeChannels.push_back(channelMap_[i->fd]);
            if (--num_ready <= 0)
            {
                break;
            }
        }
    }
}

void PollPoller::addNewChannel(Channel* channel)
{
    struct pollfd temp;
    temp.fd = channel->getFd();
    temp.events = channel->getEvents();
    pollfdList_.push_back(temp);
    channelMap_.insert(std::make_pair(channel->getFd(), channel));
}

void PollPoller::removeChannel(Channel* channel)
{
    for (auto& i :pollfdList_)
    {
        if (i.fd==channel->getFd())
        {
            i.fd = -1;
            break;
        }
    }
    for (ChannelMap::const_iterator i; i!=channelMap_.end(); ++i)
    {
        if (i->first==channel->getFd())
        {
            channelMap_.erase(i);
            break;
        }
    }
}
