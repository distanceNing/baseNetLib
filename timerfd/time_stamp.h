//
// Created by yangning on 17-10-23.
//

#ifndef BASE_NET_LIB_TIMESTAMP_H
#define BASE_NET_LIB_TIMESTAMP_H

#include <time.h>
class TimeStamp {

public:
    using PassingTime=time_t;

    TimeStamp()
            :time_(time(0)) { }

    static void printTimeNow();

    void printTime();

    PassingTime operator-(TimeStamp& rvalue);

    ~TimeStamp() { }

private:
    time_t time_;
};

#endif //!BASE_NET_LIB_TIMESTAMP_H
