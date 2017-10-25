//
// Created by yangning on 17-10-18.
//

#ifndef BASE_NET_LIB_COMMON_H
#define BASE_NET_LIB_COMMON_H

#define MAX_BUF_SIZE 1024

const int kPort=9000;

void printErrorMsg(const char* msg);

bool setFdNonBlocking(int fd);

#endif //BASE_NET_LIB_COMMON_H
