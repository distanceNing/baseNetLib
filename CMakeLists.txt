cmake_minimum_required(VERSION 3.7)
project(base_net_lib)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(include)

INCLUDE_DIRECTORIES(
        googletest/include
)

set(SOURCE_FILES


        poller/poll_poller.cpp poller/poll_poller.h
        poller/poller.h poller/poller.cpp
        poller/epoll_poller.cpp poller/epoll_poller.h

        socket/socket_buf.h socket/socket_buf.cpp
        socket/tcp_socket.cpp socket/tcp_socket.h

        event_loop.cpp event_loop.h
        tcp_server.h tcp_server.cpp
        channel.cpp channel.h
        Acceptor.h Acceptor.cpp
        tcp_connection.cpp tcp_connection.h

        timerfd/time_stamp.h timerfd/time_stamp.cpp
        timerfd/timer_fd.h  timerfd/timer_fd.cpp
        timerfd/TimeQueue.h timerfd/TimeQueue.cpp
        timerfd/SortTimerList.cpp timerfd/SortTimerList.h

        #memcached file
        #memcached/mem_request.cpp memcached/mem_request.h
        #memcached/data_structer.cpp memcached/data_structer.h
        #memcached/mem_response.cpp memcached/mem_response.h
        #memcached/user.cpp memcached/user.h
        #memcached/MemServer.cpp memcached/MemServer.h
        #memcached/mem_pool.h


        include/common.h   include/ScopeGuard.h
        main.cpp

        EventLoopThread.h EventLoopThread.cpp
        EventLoopThreadPool.cpp
        EventLoopThreadPool.h
        thread/Thread.cpp
        thread/Thread.h
        thread/thread_pool.cpp
        thread/thread_pool.h
        thread/lock.cpp
        thread/lock.h
        )


add_executable(base_net_lib ${SOURCE_FILES})
target_link_libraries(              # Start
        base_net_lib                       # Name of executable
        ${PROJECT_SOURCE_DIR}/googletest/make/gtest_main.a
        pthread# Name of library without "lib" prefix
        )
