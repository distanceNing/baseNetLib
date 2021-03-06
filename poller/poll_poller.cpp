#include <iostream>
#include "../channel.h"
#include "poll_poller.h"
#include "../timerfd/time_stamp.h"
namespace net {
TimeStamp PollPoller::Poll(int time_out, ChannelList& activeChannels)
{
    int num_ready = -1;
    std::cout << "Poll Array Size " << pollfdList_.size() << std::endl;

    num_ready = ::poll(pollfdList_.data(), pollfdList_.size(), time_out);
    //生成时间戳
    TimeStamp timeStamp = TimeStamp();
    if ( num_ready > 0 ) {
        std::cout << "Ready Event Num " << num_ready << std::endl;
        fillActiveChannel(num_ready, activeChannels);
    }
    else {
        if ( num_ready == 0 ) {
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
    for (std::vector<struct pollfd>::iterator i = pollfdList_.begin(); i != pollfdList_.end(); ++i) {
        if ( i->revents > 0 ) {
            channelMap_[i->fd]->setRetEvents(i->revents);
            activeChannels.push_back(channelMap_[i->fd]);
            if ( --num_ready <= 0 ) {
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
    pollfdList_.push_back(std::move(temp));

    auto new_channel = std::make_pair(channel->getFd(), channel);
    auto res = channelMap_.insert(std::move(new_channel));
    if ( res.second )
        channel->setIsAddInLoop(true);

}

void PollPoller::removeChannel(Channel* channel)
{
    for (auto i = pollfdList_.begin(); i != pollfdList_.end(); ++i) {
        if ( i->fd == channel->getFd()) {
            if(i->fd != pollfdList_.back().fd)
                std::swap(*i,pollfdList_.back());
            pollfdList_.pop_back();
            break;
        }
    }
    auto ite = channelMap_.find(channel->getFd());
    auto res = channelMap_.erase(ite);
    if ( res != channelMap_.end())
        channel->setIsAddInLoop(false);

}
void PollPoller::updateChannel(Channel* channel)
{
    for (auto& ite :pollfdList_) {
        if ( ite.fd == channel->getFd()) {
            ite.events = channel->getEvents();
        }
    }
}
}//namespace net