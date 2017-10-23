#ifndef _PRINT_TIME_H_
#define _PRINT_TIME_H_


#include <time.h>

#include <stdio.h>
void printTimeNow()
    
{
    time_t start_time=time(0);
    struct tm* tm=localtime(&start_time);
    printf("server start time :%d : %d : %d \n",tm->tm_hour,tm->tm_min,tm->tm_sec);

}



#endif//!_PRINT_TIME_H_
