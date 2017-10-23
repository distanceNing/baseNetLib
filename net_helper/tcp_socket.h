#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
typedef int socklen_t;

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef int SOCKET;
typedef unsigned int UINT;
typedef const char* LPCSTR;
typedef char* LPSTR;
const int SOCKET_ERROR = -1;
int GetLastError();
#endif

class TcpSocket {
    SOCKET sock;
public:

    TcpSocket();
    ~TcpSocket();
    bool CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int prot = 0);
    int Receive(void* buffer, int bufLen);
    bool Listen(int backlog = 5);
    bool Accept(TcpSocket& client_sock, char* fromIP, UINT& fromPort);
    size_t Send(void* message, int bufLen);
    bool GetPeerName(char* peerIP, UINT& peerPort);
    bool Connect(const char* conIP,const  UINT conPort);
    bool CloseSocket();
    int GetSocket() const;
};
#endif //_TCP_SOCKET_H_
