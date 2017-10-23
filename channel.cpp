
#include "channel.h"

#include <poll.h>
#include <iostream>




void Channel::handleEvent()
{
    if(revents_&POLLIN)
    {
        std::cout<<"fd "<<fd_<<"  is readable ---"<<std::endl;
        readCallBack_(fd_);
    }
    if(revents_&POLLOUT)
    {
        writeCallBack_(fd_);
    }
    if(revents_&POLLERR)
    {
        errorCallBack_(fd_);
    }
}
