#ifndef _BASE_NET_LIB_SOCKET_FD_H_
#define _BASE_NET_LIB_SOCKET_FD_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
typedef unsigned int SOCKET;
typedef unsigned int UINT;
typedef const char* LPCSTR;
typedef char* LPSTR;
#include <netinet/tcp.h>

#include "socket_buf.h"

namespace net {

class TcpSocket {
protected:
    typedef unsigned int UINT;
public:
    TcpSocket()
    {
    }
    static int create_and_bind(int port = 0, int af = AF_INET, int type = SOCK_STREAM);

    static bool sockConnect(int fd,const char* conn_ip,uint16_t conn_port);

    explicit TcpSocket(const int fd)
            :fd_(fd)
    {
    }

    virtual ~TcpSocket();

    bool CreateSocket(int port = 0, int af = AF_INET, int type = SOCK_STREAM);

    ssize_t Receive(void* buffer, size_t bufLen);

    ssize_t Receive(net::SocketBuf& buf);

    void Listen(int backlog = 5);

    int Accept(char* fromIP, UINT& fromPort);

    ssize_t Send(const void * message, size_t bufLen);

    ssize_t write_n(const void* msg,size_t buf_len);

    ssize_t read_n(void* msg,size_t buf_len);

    bool GetPeerName(char* peerIP, UINT& peerPort);

    bool Connect(const char* conIP, const UINT conPort);

    int getFd() const;

    void setTcpNoDelay();

    void shutDownWrite()
    {
        shutdown(fd_,SHUT_WR);
    }

    void shutDownRead()
    {
        shutdown(fd_,SHUT_RD);
    }
    void closeFd()
    {
        close(fd_);
    }
private:
    int fd_;

};
}//namespace net
#endif //_BASE_NET_LIB_SOCKET_FD_H_
