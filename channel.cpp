//
// Created by yangning on 17-11-28.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include <poll.h>
#include <iostream>
#include "channel.h"

void net::Channel::handleEvent()
{
    if (revents_ & POLLIN) {
        std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        if (readCallBack_)
            readCallBack_();
    }
    if (revents_ & POLLOUT) {
        if (writeCallBack_)
            writeCallBack_();
    }
    if (revents_ & POLLERR) {
        if (errorCallBack_)
            errorCallBack_();
    }

}


