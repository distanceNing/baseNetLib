//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Acceptor.h"
namespace net {

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
}//namespace net
