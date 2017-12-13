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
namespace net {
void Channel::handleEvent()
{

    assert(isAddInLoop_);
    if ( revents_ & POLLIN ) {
        std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        if ( readCallBack_ )
            readCallBack_();
    }
    if ( revents_ & POLLOUT ) {
        if ( writeCallBack_ )
            writeCallBack_();
    }
    if ( revents_ & POLLERR ) {
        if ( errorCallBack_ )
            errorCallBack_();
    }

}

void Channel::setIsAddInLoop(bool isAddInLoop)
{
    this->isAddInLoop_ = isAddInLoop;
}
}//namespace net

