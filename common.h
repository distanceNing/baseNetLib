//
// Created by yangning on 17-10-18.
//

#ifndef BASE_NET_LIB_COMMON_H
#define BASE_NET_LIB_COMMON_H
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#define MAX_BUF_SIZE 4096

const int kPort = 9000;

inline void printErrorMsg(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

inline bool setFdNonBlocking(int fd)
{
    int flag = fcntl(fd, F_SETFL, O_NONBLOCK);
    if ( flag == -1 ) {
        printErrorMsg("setFdNonBlocking");
    }
    return true;
}

inline int64_t nowTime()
{
    struct timeval tm;
    if ( gettimeofday(&tm, 0) < 0 )
        printErrorMsg("gettimeofday");
    return (int64_t) tm.tv_sec * 1000 * 1000 + (int64_t) tm.tv_usec;
}

struct IpAddress {
  std::string ip;
  unsigned int port;

  IpAddress(const char* ip, unsigned int port)
          :ip(ip), port(port)
  {
  }
};

inline ssize_t send_file(const char* filename, int sock)
{
    int size;
    int fd = open(filename, O_RDONLY);
    assert(fd > 0);
    struct stat stat_buf;
    fstat(fd, &stat_buf);
    return sendfile(sock, fd, NULL, (size_t) stat_buf.st_size);
}
#endif //BASE_NET_LIB_COMMON_H
