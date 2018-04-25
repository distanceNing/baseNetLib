//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Acceptor.h"
#include "event_loop.h"
namespace net {
Acceptor::Acceptor(unsigned listenPort, EventLoop* loop)
        :ownEventLoop_(loop), listenSock_(TcpSocket::create_and_bind(listenPort)),
         listenChannel_(loop, listenSock_.getFd()), listening_(false), listenPort_(listenPort)
{
    setFdNonBlocking(listenSock_.getFd());
    listenChannel_.setReadCallBack(std::bind(&Acceptor::handleRead, this));
}

void Acceptor::handleRead()
{
    char conn_ip[32];
    unsigned conn_port = 0;
    int client_fd;
    if ((client_fd = listenSock_.Accept(conn_ip, conn_port)) < 0)
        printErrorMsg("accept");
    //设置socke为非阻塞
    setFdNonBlocking(client_fd);
    //执行newconnection回调
    if (newConnetcioncb_)
        newConnetcioncb_(client_fd, IpAddress(conn_ip, conn_port));
    else
        close(client_fd);
}
void Acceptor::listen()
{
    listening_ = true;
    listenSock_.Listen();
    ownEventLoop_->addNewChannel(&listenChannel_);
    listenChannel_.enableReading();
    std::cout << "server is running on  " << listenPort_ << " ----- \n";
}

}//namespace net
