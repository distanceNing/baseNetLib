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
            Fd* active_fd=channelMap_[i->fd];
            active_fd->setRetEvents(i->revents);
            activeChannels.push_back(active_fd);
            if (--num_ready <= 0)
            {
                break;
            }
        }
    }
}

void PollPoller::addNewChannel(Fd* channel)
{
    struct pollfd temp;
    temp.fd = channel->getFd();
    temp.events = channel->getEvents();
    pollfdList_.push_back(temp);
    auto new_channel=std::make_pair(channel->getFd(),channel);
    channelMap_.insert(new_channel);
}

void PollPoller::removeChannel(Fd* channel)
{
    for (auto& i :pollfdList_)
    {
        if (i.fd==channel->getFd())
        {
            i.fd = -1;
            break;
        }
    }
    auto ite= channelMap_.find(channel->getFd());
    channelMap_.erase(ite);
}
