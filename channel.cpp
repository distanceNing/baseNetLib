
#include "channel.h"

#include <poll.h>
#include <iostream>

void Channel::handleEvent()
{
    if (revents_ & POLLIN)
    {
        std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        readCallBack_(static_cast<void*>(&fd_));
    }
    if (revents_ & POLLOUT)
    {
        writeCallBack_(static_cast<void*>(&fd_));
    }
    if (revents_ & POLLERR)
    {
        errorCallBack_(static_cast<void*>(&fd_));
    }
}
