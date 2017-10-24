#include "tcp_socket.h"

#ifndef _WIN32
int GetLastError()
{
    return errno;
}
#endif // !_WIN32

TcpSocket::TcpSocket()
{
    sock = -1;
#ifdef _WIN32
    WSADATA iData = { 0 };
    int iResult = WSAStartup(0x0202, &iData);
#endif // !_WIN32

}

TcpSocket::~TcpSocket()
{
#ifdef _WIN32
    closesocket(sock);

#else
    close(sock);
#endif
}

bool TcpSocket::CreateSocket( int prot,int af, int type)
{
    sock = socket(af, type, 0);
    if (sock==SOCKET_ERROR)
        return false;
    sockaddr_in sa = {af, htons(prot)};
    int flag = bind(sock, (sockaddr*) &sa, sizeof(sa));
    return flag<0 ? false : true;
}

bool TcpSocket::Listen(int backlog)
{
    listen(sock, backlog);
    return true;
}

int TcpSocket::Receive(void* buffer, int bufLen)
{
    return recv(sock, (LPSTR) buffer, bufLen, 0);
}





bool TcpSocket::Accept(TcpSocket& clientSock, char* fromIP, UINT& fromPort)
{
    sockaddr_in from = {AF_INET};
    socklen_t len = sizeof(from);
    clientSock.sock = accept(sock, (sockaddr*) &from, &len);
    strcpy(fromIP, inet_ntoa(from.sin_addr));
    fromPort = htons(from.sin_port);
    return true;
}

size_t TcpSocket::Send(void* message, int buflen)
{
    return send(sock, (LPCSTR) message, buflen, 0);
}

bool TcpSocket::GetPeerName(char* peerIP, UINT& peerPort)
{
    sockaddr_in from = {AF_INET};
    socklen_t len = sizeof(from);
    if (getpeername(sock, (sockaddr*) &from, &len)<0) {
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
    sockaddr_in conAddr = {AF_INET};
#ifdef _WIN32
    conAddr.sin_addr.S_un.S_addr = inet_addr(conIP);

#else
    conAddr.sin_addr.s_addr = inet_addr(conIP);
#endif
    conAddr.sin_port = htons(conPort);
    socklen_t len = sizeof(conAddr);
    int flag = connect(sock, (sockaddr*) &conAddr, len);
    return flag < 0 ? false : true ;
}

bool TcpSocket::CloseSocket()
{
#ifdef _WIN32
    closesocket(sock);

#else
    close(sock);
#endif
    return true;
}
int TcpSocket::GetSocket() const
{
    return sock;
}

