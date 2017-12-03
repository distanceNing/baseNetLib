#include "tcp_socket.h"
#include "../common.h"
#include <cstdint>
#include <iostream>
namespace net {
bool TcpSocket::CreateSocket(int port, int af, int type)
{
    fd_ = socket(af, type, 0);
    if ( fd_ < 0 )
        return false;
    int on = 1;
    if ((setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0 ) {
        return false;
    }
    sockaddr_in sa;
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(static_cast<uint16_t>(port));

    int flag = bind(fd_, (sockaddr*) &sa, sizeof(sa));
    return flag >= 0;
}

void TcpSocket::Listen(int backlog)
{
    listen(fd_, backlog);
}

ssize_t TcpSocket::Receive(void* buffer, size_t buf_len)
{
    assert(buffer != NULL);
    return recv(fd_, static_cast<char*>(buffer), buf_len, 0);
}

ssize_t TcpSocket::Receive(net::SocketBuf& buf)
{
    ssize_t size = recv(fd_, buf.writeBegin(), buf.writeableBytes(), 0);
    if(size > 0)
        buf.writeSkip(static_cast<size_t>(size));
    return size;
}

int TcpSocket::Accept(char* fromIP, UINT& fromPort)
{
    assert(fromIP != NULL);
    sockaddr_in from;
    memset(&from, 0, sizeof(struct sockaddr_in));
    from.sin_family = AF_INET;
    socklen_t len = sizeof(from);
    int clientSock = -1;
    if ((clientSock = accept(fd_, (sockaddr*) &from, &len)) < 0 )
        return clientSock;
    strcpy(fromIP, inet_ntoa(from.sin_addr));
    fromPort = htons(from.sin_port);
    return clientSock;
}

ssize_t TcpSocket::Send(const void* message, size_t buf_len)
{
    assert(message != NULL);
    return send(fd_, message, buf_len, MSG_NOSIGNAL);
}

bool TcpSocket::GetPeerName(char* peerIP, UINT& peerPort)
{
    assert(peerIP != NULL);
    sockaddr_in from;
    memset(&from, 0, sizeof(struct sockaddr_in));
    from.sin_family = AF_INET;
    socklen_t len = sizeof(from);
    if ( getpeername(fd_, (sockaddr*) &from, &len) < 0 ) {
        return false;
    }
    else {
        strcpy(peerIP, inet_ntoa(from.sin_addr));
        peerPort = htons(from.sin_port);
    }
    return true;;
}

bool TcpSocket::Connect(const char* conIP, const UINT conPort)
{
    assert(conIP != NULL);
    sockaddr_in conAddr;
    memset(&conAddr, 0, sizeof(struct sockaddr_in));
    conAddr.sin_family = AF_INET;
    conAddr.sin_addr.s_addr = inet_addr(conIP);
    conAddr.sin_port = htons(static_cast<uint16_t>(conPort));
    socklen_t len = sizeof(conAddr);
    int flag = connect(fd_, (sockaddr*) &conAddr, len);
    return flag >= 0;
}

TcpSocket::~TcpSocket()
{
    closeFd();
}
int TcpSocket::getFd() const
{
    return fd_;
}
ssize_t TcpSocket::write_n(const void* msg, size_t buf_len)
{
    assert(msg != NULL);
    ssize_t send_size = 0;
    ssize_t a_send_size;
    while ((a_send_size = ::write(fd_, (char*) msg + send_size, buf_len - send_size)) > 0) {
        send_size += a_send_size;
        if ( send_size == buf_len )
            break;
    }
    return send_size;
}
ssize_t TcpSocket::read_n(void* msg, size_t buf_len)
{
    assert(msg != NULL);
    ssize_t recv_size = 0;
    ssize_t a_recv_size;
    while ((a_recv_size = ::read(fd_, (char*) msg + recv_size, buf_len - recv_size)) > 0) {
        recv_size += a_recv_size;
        if ( recv_size == buf_len )
            break;
    }
    return recv_size;
}
int TcpSocket::create_and_bind(int port, int af, int type)
{
    int fd;
    fd = socket(af, type, 0);
    if ( fd < 0 )
        printErrorMsg("socket");
    int on = 1;
    //address already use
    if ((setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0 ) {
        printErrorMsg("setsockopt");
    }
    sockaddr_in sa;
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(static_cast<uint16_t>(port));
    if ( bind(fd, (sockaddr*) &sa, sizeof(sa)) < 0 )
        printErrorMsg("bind");
    return fd;
}
void TcpSocket::setTcpNoDelay()
{
    int on = 1;
    if ( setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, (void*) &on, sizeof(on)))
        printErrorMsg("setsockpot");
}
bool TcpSocket::sockConnect(int fd,const char* conn_ip, uint16_t conn_port)
{
    assert(conn_ip != NULL);
    sockaddr_in conAddr;
    memset(&conAddr, 0, sizeof(struct sockaddr_in));
    conAddr.sin_family = AF_INET;
    conAddr.sin_addr.s_addr = inet_addr(conn_ip);
    conAddr.sin_port = htons(static_cast<uint16_t>(conn_port));
    socklen_t len = sizeof(conAddr);
    int flag = ::connect(fd, (sockaddr*) &conAddr, len);
    return flag >= 0;
}
}//namespace net



