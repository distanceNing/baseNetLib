//
// Created by yangning on 17-10-18.
//

#ifndef BASE_NET_LIB_COMMON_H
#define BASE_NET_LIB_COMMON_H

#define MAX_BUF_SIZE 1024

#include "common.h"
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>

const int kPort=9000;
inline void printErrorMsg(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

inline bool setFdNonBlocking(int fd)
{
    int flag = fcntl(fd,F_SETFL,O_NONBLOCK);
    if(flag == -1)
    {
        printErrorMsg("setFdNonBlocking");
    }
    return true;
}


#endif //BASE_NET_LIB_COMMON_H
