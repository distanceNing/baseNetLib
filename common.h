//
// Created by yangning on 17-10-18.
//

#ifndef EPOLL_COMMON_H
#define EPOLL_COMMON_H
const int kPort=9000;

void printErrorMsg(const char* msg);

bool setFdNonBlocking(int fd);

#endif //EPOLL_COMMON_H
