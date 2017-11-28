//
// Created by yangning on 17-10-23.
//

#include "time_stamp.h"
#include <cstdio>
namespace net {
void TimeStamp::printTime()
{
    struct tm* tm = localtime(&time_);
    printf("Time is :%d : %d : %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void TimeStamp::printTimeNow()
{
    time_t start_time = time(0);
    struct tm* tm = localtime(&start_time);
    printf("Now time :%d : %d : %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

TimeStamp::PassingTime TimeStamp::operator-(TimeStamp& rvalue)
{
    return time_ - rvalue.time_;
}
}//namespace net