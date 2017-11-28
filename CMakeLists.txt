cmake_minimum_required(VERSION 3.7)
project(base_net_lib)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        event_loop.cpp
        event_loop.h
        main.cpp
        poller/poll_poller.cpp
        poller/poll_poller.h
        timerfd/timer_fd.h common.h
        poller/poller.h poller/epoll_poller.cpp poller/epoll_poller.h
        timerfd/time_stamp.cpp timerfd/time_stamp.h timerfd/timer_fd.cpp
        tcp_server.h tcp_server.cpp
        thread/Thread.cpp
        thread/Thread.h
        thread/thread_pool.cpp
        thread/thread_pool.h
        thread/lock.cpp
        thread/lock.h
        socket/socket_buf.h socket/socket_buf.cpp
        socket/tcp_socket.cpp socket/tcp_socket.h
        channel.cpp channel.h
        Acceptor.h Acceptor.cpp
        )
link_libraries(pthread)

add_executable(base_net_lib ${SOURCE_FILES})