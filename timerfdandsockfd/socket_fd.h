#ifndef _BASE_NET_LIB_SOCKET_FD_H_
#define _BASE_NET_LIB_SOCKET_FD_H_

#include "Fd.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int GetLastError();
namespace net {
class SocketFd : public Fd {
protected:
    typedef unsigned int UINT;
    const int SOCKET_ERROR = -1;
public:
    SocketFd(EventLoop* own_loop);

    bool CreateSocket(int port = 0, int af = AF_INET, int type = SOCK_STREAM);

    ssize_t Receive(void* buffer, size_t bufLen);

    void Listen(int backlog = 5);

    int Accept(char* fromIP, UINT& fromPort);

    ssize_t Send(void* message, size_t bufLen);

    bool GetPeerName(char* peerIP, UINT& peerPort);

    bool Connect(const char* conIP, const UINT conPort);

};
}//namespace net
#endif //_BASE_NET_LIB_SOCKET_FD_H_
