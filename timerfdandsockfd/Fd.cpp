//
// Created by yangning on 17-10-24.
//

#include <zconf.h>
#include "Fd.h"
#include "../event_loop.h"
namespace net{
void Fd::setErrorCallBack(Fd::EventCallBack call_back)
{
    errorCallBack_ = call_back;
}
void Fd::setEvents(int events)
{
    events_ = events;
}
short Fd::getEvents() const
{
    return events_;
}
void Fd::setWriteCallBack(Fd::EventCallBack call_back)
{
    writeCallBack_ = call_back;
}
int Fd::getFd() const
{
    return fd_;
}
void Fd::setRetEvents(int ret_events)
{
    revents_ = ret_events;
}
void Fd::closeFd()
{
    close(fd_);

}
void Fd::setReadCallBack(Fd::EventCallBack call_back)
{
    readCallBack_ = call_back;
}
void Fd::resetFd(int fd)
{
    fd_ =fd;
}
void Fd::removeSelf()
{
    ownEventLoop_->removeChannel(this);
}
void Fd::handleEvent()
{
    if (revents_ & POLLIN)
    {
        std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        readCallBack_();
    }
    if (revents_ & POLLOUT)
    {
        writeCallBack_();
    }
    if (revents_ & POLLERR)
    {
        errorCallBack_();
    }

}
}//namespace net