//
// Created by yangning on 17-11-29.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "event_loop.h"
#include "Acceptor.h"
#include "common.h"

void connectionCallBack(int fd,IpAddress ipAddress)
{
    const char* hello="hello world";
    char buffer[MAX_BUF_SIZE]={'\0'};
    ::read(fd,buffer,MAX_BUF_SIZE);
    ::write(fd,hello ,strlen(hello));
    close(fd);
}

int main()
{

    net::EventLoop loop(net::POLL);

    net::Acceptor acceptor(kPort,&loop,connectionCallBack);

    acceptor.listen();

    loop.startLoop();
    return EXIT_SUCCESS;
}