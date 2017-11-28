#include "poll_poller.h"

#include <stdlib.h>
#include <iostream>
namespace net {
TimeStamp PollPoller::Poll(int time_out, ChannelList& activeChannels)
{
    int num_ready = -1;
    std::cout << "Poll Array Size " << pollfdList_.size() << std::endl;

    num_ready = ::poll(pollfdList_.data(), pollfdList_.size(), time_out);
    //生成时间戳
    TimeStamp timeStamp = TimeStamp();
    if (num_ready > 0) {
        std::cout << "Ready Event Num " << num_ready << std::endl;
        fillActiveChannel(num_ready, activeChannels);
    }
    else {
        if (num_ready == 0) {
            std::cout << "No Event Happened-----" << std::endl;
        }
        else {
            printErrorMsg("poll");
        }
    }
    return timeStamp;
}

void PollPoller::fillActiveChannel(int num_ready, ChannelList& activeChannels)
{
    for (std::vector<struct pollfd>::iterator i = pollfdList_.begin(); i != pollfdList_.end(); ++i)
    {
        if (i->revents > 0) {
            channelMap_[i->fd]->setRetEvents(i->revents);
            activeChannels.push_back(channelMap_[i->fd]);
            if (--num_ready <= 0) {
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
    pollfdList_.push_back(std::move(temp));

    auto new_channel = std::make_pair(channel->getFd(), channel);
    channelMap_.insert(std::move(new_channel));
}

void PollPoller::removeChannel(Fd* channel)
{
    for (auto i = pollfdList_.begin(); i != pollfdList_.end(); ++i) {
        if (i->fd == channel->getFd()) {
            pollfdList_.erase(i);
            break;
        }
    }
    auto ite = channelMap_.find(channel->getFd());
    channelMap_.erase(ite);
}
}//namespace net