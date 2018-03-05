//
// Created by yangning on 17-11-29.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "Acceptor.h"
#include "../common.h"

int main()
{

    net::EventLoop loop(net::POLL);

    net::Acceptor acceptor(kPort, &loop);

    acceptor.setNewConnetcionCallBack([](int fd, IpAddress ipAddress) {
      printf("a new connection fd is %d ,ip : %s  port : %d \n", fd, ipAddress.ip.c_str(), ipAddress.port);
      const char* hello="hello world";
      char buffer[MAX_BUF_SIZE]={'\0'};
      ::write(fd,hello ,strlen(hello));
      close(fd);
    });

    acceptor.listen();

    loop.startLoop();

    return EXIT_SUCCESS;
}