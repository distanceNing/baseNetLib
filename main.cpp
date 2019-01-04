//
// Created by yangning on 17-10-25.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "EventLoopThreadPool.h"
#include "gtest/gtest.h"
#include "tcp_server.h"
#include "tcp_connection.h"

#include "event_loop.h"

#include "Server.h"
#define __TESTING
int main(int argc, char* argv[])
{
#ifdef __TESTING
    //::testing::FLAGS_gtest_color="yes";
    //::testing::InitGoogleTest(&argc, argv);
    net::EventLoop loop(net::POLL);
    Server server(&loop,0);
    server.run();

/**
    net::EventLoop loop(net::POLL);
    //单线程环境
    //net::EventLoopThreadPool loop_pool(&loop,0);

    //EXPECT_EQ(&loop,loop_pool.getNextLoop());
    //net::EventLoopThreadPool loop_pool(&loop,4);

    //EXPECT_EQ(&loop,loop_pool.getNextLoop());

    net::TcpServer tcpServer(kPort,&loop,1);
    loop.assertInLoopThread();

    tcpServer.setClienCloseCallBack([](net::TcpConnectionPtr connection){
      printf("fd is %d closed \n",connection->getFd());
    });

    tcpServer.setClientReadCallBack([](net::TcpConnection& connection,net::SocketBuf* buf){
      connection.send(buf->readBegin(),buf->readableBytes());
      //printf("%s",buf->readBegin());
      buf->skip(buf->readableBytes());

    });

    tcpServer.setClienErrorCallBack([](){
      printErrorMsg("error");
    });

    tcpServer.setNewConnCallBack([](int fd, const IpAddress& ipAddress) {
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
    });

    tcpServer.serverStart();
  
*///  return RUN_ALL_TESTS();
    return 0;
#else
    return 0;
#endif //__TESTING
}

