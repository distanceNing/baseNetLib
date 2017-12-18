//
// Created by yangning on 17-10-23.
//

#include <iostream>
#include "epoll_poller.h"
#include "../headers/common.h"
#include "../channel.h"
#include "../timerfd/time_stamp.h"
namespace net {
EpollPoller::EpollPoller()
        :epollEventList_(kInitEpollEventSize), epollFd_(epoll_create1(0))
{
    if (epollFd_ < 0)
        perror("epoll create");
}

TimeStamp EpollPoller::Poll(int time_out, Poller::ChannelList& activeChannels)
{
    int num_ready = epoll_wait(epollFd_, epollEventList_.data(), static_cast<int >(epollEventList_.size()), time_out);
    TimeStamp timeStamp = TimeStamp();
    if (num_ready > 0) {
        std::cout << "Ready Event Num " << num_ready << std::endl;
        fillActiveChannel(num_ready, activeChannels);

        //当返回的事件大小和epollEventList长度一样时,进行扩充
        if (epollEventList_.size() == num_ready) {
            epollEventList_.resize(epollEventList_.size() << 2);
        }
    }
    else {
        if (num_ready == 0) {
            std::cout << "No Event Happened-----" << std::endl;
        }
        else {
            printErrorMsg("Epoll Error");
        }
    }
    return timeStamp;
}

void EpollPoller::addNewChannel(Channel* channel)
{
    struct epoll_event event;
    setFdNonBlocking(channel->getFd());
    event.data.fd = channel->getFd();
    event.events = static_cast<uint32_t>(channel->getEvents()) | EPOLLET;
    epoll_ctl(epollFd_, EPOLL_CTL_ADD, channel->getFd(), &event);
    channelMap_.insert(std::make_pair(channel->getFd(), channel));
}

void EpollPoller::removeChannel(Channel* channel)
{
    struct epoll_event event;
    event.data.fd = channel->getFd();
    event.events = static_cast<uint32_t>(channel->getEvents()) | kEPOLL_MODE;
    //从内核注册表上删除文件描述符
    epoll_ctl(epollFd_, EPOLL_CTL_DEL, channel->getFd(), &event);
    //从channelMap删除
    auto ite = channelMap_.find(channel->getFd());
    channelMap_.erase(ite);
}

void EpollPoller::fillActiveChannel(int num_ready, Poller::ChannelList& activeChannels)
{
    for (auto i = epollEventList_.begin(); i != epollEventList_.end(); ++i) {
        channelMap_[i->data.fd]->setRetEvents(i->events);
        activeChannels.push_back(channelMap_[i->data.fd]);
        if (--num_ready <= 0) {
            break;
        }
    }
}
}//namespace net
