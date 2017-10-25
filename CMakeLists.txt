cmake_minimum_required(VERSION 3.7)
project(poller)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        event_loop.cpp
        event_loop.h
        main.cpp
        poller/poll_poller.cpp
        poller/poll_poller.h
        timerfdandsockfd/Fd.cpp
        timerfdandsockfd/Fd.h
        timerfdandsockfd/socket_fd.cpp
        timerfdandsockfd/socket_fd.h
        timerfdandsockfd/timer_fd.h common.cpp common.h poller/poller.cpp
        poller/poller.h poller/epoll_poller.cpp poller/epoll_poller.h
        timerfdandsockfd/time_stamp.cpp timerfdandsockfd/time_stamp.h timerfdandsockfd/timer_fd.cpp
        tcp_server.h tcp_server.cpp
        thread/Thread.cpp
        thread/Thread.h
        thread/thread_pool.cpp
        thread/thread_pool.h
        )
link_libraries(pthread)

add_executable(base_net_lib ${SOURCE_FILES})