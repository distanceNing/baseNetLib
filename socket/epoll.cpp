//
// Created by yangning on 17-10-18.
//

#include "epoll.h"
#include "../common.h"


void Epoll::handleEvent(int ready_num)
{
    //处理文件描述符上发生的事件
    for (int i = 0; i < ready_num; ++i)
    {
        int fd=epollEventList_[i].data.fd;
        fd_map_.find(fd)->second();
    }
}
void Epoll::addNewFd(int fd,EventCallBack& cb)
{
    setFdNonBlocking(fd);
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    int flag = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event);
    if (flag < 0)
        printErrorMsg("epoll_ctl");
    fd_map_.insert(std::make_pair(fd,cb));

}
void Epoll::epollWait()
{
    int ready_num = epoll_wait(epoll_fd_, epollEventList_.data(), static_cast<int>(epollEventList_.size()),
            MAYBE_TIME_OUT);

    if (ready_num < 0) {
        printErrorMsg("epoll_wait");
    }

    if (ready_num == 0) {
        std::cout << "No Event Happened --- \n";
    }
    //当返回的准备好的事件和pollEventList的长度相同时,进行扩充.
    if (epollEventList_.size() == static_cast<unsigned long>(ready_num))
    {
        epollEventList_.resize(epollEventList_.size() * 2);
    }

    handleEvent(ready_num);
}
void Epoll::removeFd(int fd)
{
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
    fd_map_.erase(fd);
}


