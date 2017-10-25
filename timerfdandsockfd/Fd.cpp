//
// Created by yangning on 17-10-24.
//

#include <zconf.h>
#include "Fd.h"

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
void Fd::setReadCallBack(Fd::EventCallBack call_back, void* arg)
{
    readCallBack_ = call_back;
    callBackArg_=arg;
}
