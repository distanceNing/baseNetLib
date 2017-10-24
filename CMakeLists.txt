cmake_minimum_required(VERSION 3.7)
project(poller)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        channel.cpp
        channel.h
        event_loop.cpp
        event_loop.h
        main.cpp
        poller/poll_poller.cpp
        poller/poll_poller.h
        net_helper/tcp_socket.cpp
        net_helper/tcp_socket.h
        timerfd/timer.h common.cpp common.h poller/poller.cpp
        poller/poller.h poller/epoll_poller.cpp poller/epoll_poller.h
        timerfd/time_stamp.cpp timerfd/time_stamp.h timerfd/timer.cpp
        tcp_server.h tcp_server.cpp
        )

add_executable(base_net_lib ${SOURCE_FILES})