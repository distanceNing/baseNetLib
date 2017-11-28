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
#include "../common.h"


#include "socket_buf.h"
namespace net {


class TcpSocket {
protected:
	typedef unsigned int UINT;
public:
	TcpSocket() {

	}
	static int create_and_bind(int port = 0, int af = AF_INET, int type = SOCK_STREAM){
		int fd;
		fd = socket(af, type, 0);
		if (fd < 0)
			printErrorMsg("socket");
		int on=1;
		if((setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
		{
			printErrorMsg("setsockopt");
		}
		sockaddr_in sa;
		memset(&sa, 0, sizeof(struct sockaddr_in));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(static_cast<uint16_t>(port));
		if(bind(fd, (sockaddr*)&sa, sizeof(sa)) < 0)
			printErrorMsg("bind");
		return fd;
	}
	explicit TcpSocket(const int fd):fd_(fd) {
	}

	virtual ~TcpSocket();

	bool CreateSocket(int port = 0, int af = AF_INET, int type = SOCK_STREAM);

	ssize_t Receive(void* buffer, size_t bufLen);

	ssize_t Receive(net::SocketBuf& buf);

	void Listen(int backlog = 5);

	int Accept(char* fromIP, UINT& fromPort);

	ssize_t Send(const char* message, size_t bufLen);

	bool GetPeerName(char* peerIP, UINT& peerPort);

	bool Connect(const char* conIP, const  UINT conPort);

	int getFd() const;

	void closeFd()
	{
		close(fd_);
	}
private:
	int fd_;

};
}//namespace net
#endif //_BASE_NET_LIB_SOCKET_FD_H_
