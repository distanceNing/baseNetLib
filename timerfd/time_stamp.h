//
// Created by yangning on 17-10-23.
//

#ifndef BASE_NET_LIB_TIMESTAMP_H
#define BASE_NET_LIB_TIMESTAMP_H

#include <time.h>
#include <sys/time.h>
#include "../common.h"

namespace net {

class TimeStamp {

public:
    using PassingTime=int64_t;
    /*
     * @descriprion:获取当前的时间
     * @param: void
     * @return: 单位为us
     */
    static int64_t nowTime()
    {
        struct timeval tm;
        if ( gettimeofday(&tm, 0) < 0 )
            printErrorMsg("gettimeofday");
        return (int64_t) tm.tv_sec * 1000 * 1000 + (int64_t) tm.tv_usec;
    }

    static void printTimeNow();
    TimeStamp()
            :time_us_(nowTime())
    {
    }

    PassingTime operator-(TimeStamp& rvalue);

    ~TimeStamp()
    {
    }

private:
    int64_t time_us_;
};
}//namespace net
#endif //!BASE_NET_LIB_TIMESTAMP_H
