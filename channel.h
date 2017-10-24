#ifndef _CHANELL_H_
#define _CHANELL_H_
#include <boost/utility.hpp>

typedef void (* EventCallBack)(void *);

class Channel : boost::noncopyable {

public:
    Channel(const int fd,
            EventCallBack rcb = NULL,
            EventCallBack wcb = NULL,
            EventCallBack ecb = NULL
    )
            :fd_(fd), writeCallBack_(wcb), readCallBack_(rcb), errorCallBack_(ecb) { }

    void setWriteCallBack(EventCallBack call_back)
    {
        writeCallBack_ = call_back;
    }

    void setReadCallBack(EventCallBack call_back)
    {
        readCallBack_ = call_back;
    }

    void setErrorCallBack(EventCallBack call_back)
    {
        errorCallBack_ = call_back;
    }

    void setEvents(int events)
    {
        events_ = events;
    }


    short getEvents() const
    {
        return events_;
    }
    void handleEvent();

    short getFd() const
    {
        return fd_;
    }

    ~Channel() { }

private:

    const int fd_;
    short events_;
    short revents_;
    EventCallBack writeCallBack_;
    EventCallBack readCallBack_;
    EventCallBack errorCallBack_;
};
#endif//!_CHANELL_H_
