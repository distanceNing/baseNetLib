#include "socket_fd.h"
#include <iostream>


SocketFd::SocketFd()
{
    fd_ = -1;
}


bool SocketFd::CreateSocket( int prot,int af, int type)
{
    fd_ = socket(af, type, 0);
    if (fd_==SOCKET_ERROR)
        return false;
    sockaddr_in sa = {af, htons(prot)};
    int flag = bind(fd_, (sockaddr*) &sa, sizeof(sa));
    return flag >= 0 ;
}

void SocketFd::Listen(int backlog)
{
    listen(fd_, backlog);
}

ssize_t SocketFd::Receive(void* buffer, size_t buf_len)
{
    return recv(fd_, static_cast<char*>(buffer), buf_len, 0);
}

bool SocketFd::Accept(SocketFd& clientSock, char* fromIP, UINT& fromPort)
{
    sockaddr_in from = {AF_INET};
    socklen_t len = sizeof(from);
    clientSock.fd_ = accept(fd_, (sockaddr*) &from, &len);
    strcpy(fromIP, inet_ntoa(from.sin_addr));
    fromPort = htons(from.sin_port);
    return true;
}

ssize_t SocketFd::Send(void* message, size_t buf_len)
{
    return send(fd_, static_cast<char*>(message) , buf_len, 0);
}

bool SocketFd::GetPeerName(char* peerIP, UINT& peerPort)
{
    sockaddr_in from = {AF_INET};
    socklen_t len = sizeof(from);
    if (getpeername(fd_, (sockaddr*) &from, &len)<0) {
        return false;
    }
    else {
        strcpy(peerIP, inet_ntoa(from.sin_addr));
        peerPort = htons(from.sin_port);
    }
    return true;;
}

bool SocketFd::Connect(const char* conIP, const UINT conPort)
{
    sockaddr_in conAddr = {AF_INET};
    conAddr.sin_addr.s_addr = inet_addr(conIP);
    conAddr.sin_port = htons(static_cast<uint16_t>(conPort));
    socklen_t len = sizeof(conAddr);
    int flag = connect(fd_, (sockaddr*) &conAddr, len);
    return flag >= 0;
}

void SocketFd::handleEvent()
{
    if (revents_ & POLLIN)
    {
        std::cout << "fd " << fd_ << "  is readable ---" << std::endl;
        readCallBack_(static_cast<void*>(&fd_));
    }
    if (revents_ & POLLOUT)
    {
        writeCallBack_(static_cast<void*>(&fd_));
    }
    if (revents_ & POLLERR)
    {
        errorCallBack_(static_cast<void*>(&fd_));
    }

}

bool SocketFd::CloseSocket()
{
    close(fd_);
    return true;
}

SocketFd::~SocketFd()
{
    close(fd_);
}

