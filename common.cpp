//
// Created by yangning on 17-10-16.
//

#include "common.h"

#include <cstdio>
#include <cstdlib>

void printErrorMsg(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
