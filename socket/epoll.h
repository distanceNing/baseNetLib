//
// Created by yangning on 17-10-18.
//

#ifndef EPOLL_EPOLL_TEST_H
#define EPOLL_EPOLL_TEST_H
#include "../common.h"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <cstring>
#define INIT_SIZE 16

#define MAYBE_TIME_OUT -1

#define EPOLL_FLAGS 0

typedef int ERROR_TYPE;

class Epoll{
public:
    using EpollEventList=std::vector<struct epoll_event>;
    using EventCallBack=std::function<void()>;
    using FdMap =std::map<int,EventCallBack>;

    Epoll():epollEventList_(INIT_SIZE),epoll_fd_(epoll_create1(EPOLL_FLAGS)){
        if (epoll_fd_ < 0)
            printErrorMsg("epoll create");
    }

    void addNewFd(int fd,EventCallBack& cb);

    void removeFd(int fd);

    void epollWait();

    int getEpollFd()const
    {
        return epoll_fd_;
    }

private:
    void handleEvent(int ready_num);
    int epoll_fd_;
    FdMap fd_map_;
    EpollEventList epollEventList_;
};


ERROR_TYPE epollHandleConnect( int listenFd);

#endif //EPOLL_EPOLL_TEST_H
