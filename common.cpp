//
// Created by yangning on 17-10-18.
//

#include "common.h"
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>

void printErrorMsg(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

bool setFdNonBlocking(int fd)
{
    int flag = fcntl(fd,F_SETFL,O_NONBLOCK);
    if(flag == -1)
    {
        printErrorMsg("setFdNonBlocking");
    }
    return true;
}

