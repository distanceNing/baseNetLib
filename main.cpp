#include "socket/epoll.h"
#include "socket/tcp_socket.h"
#include "common.h"
#include "Request.h"
#include "Response.h"

void listenRcb(int listenFd, Epoll* epoll, DataStructer* dataStructer);

void clientRcb(int fd, Epoll& epoll, DataStructer* dataStructer);

static bool isLooping = true;

int main(int argc, char* argv[])
{
    net::TcpSocket listen_sock;
    if ( !listen_sock.CreateSocket(kPort))
        printErrorMsg("crete socket");
    listen_sock.Listen();
    printf("memcached is running on %d \n", kPort);
    DataStructer dataStructer;
    Epoll epoll;
    Epoll::EventCallBack fun = std::bind(listenRcb, listen_sock.getFd(), &epoll, &dataStructer);
    epoll.addNewFd(listen_sock.getFd(), fun);
    while (isLooping)
        epoll.epollWait();
    return 0;
}

void clientRcb(int fd, Epoll& epoll, DataStructer* dataStructer)
{
    net::SocketBuf read_buf;
    ssize_t read_size = 0;
    ssize_t size;
    while ((size = read_buf.readFromFd(fd)) > 0) {
        read_size += size;
    }
    if ( read_size == 0 ) {
        epoll.removeFd(fd);
        //关闭client socket
        close(fd);
        std::cout << "client fd " << fd << " close --\n";
    }
    else {
        Request request(read_buf);
        if ( request.parse() == PARSE_OK ) {
            if ( request.getRequestType() == QUIT ) {
                epoll.removeFd(fd);
                //关闭client socket
                close(fd);
                std::cout << "client fd " << fd << " close --\n";
            }
            else {
                Response response(dataStructer);
                switch (request.getRequestType()) {
                case SET: {
                    response.handleSet(request.getKey(), request.getValueInfo());
                    break;
                }
                case GET: {
                    response.handleGet(request.getKey());
                    break;
                }
                default:break;

                }
                ::write(fd, response.getResponse(), response.getResponseLength());
                //dataStructer.insert(request.getKey().c_str(), request.getValueInfo());
            }
        }
    }

}

void listenRcb(int listenFd, Epoll* epoll, DataStructer* dataStructer)
{
    char connIP[32] = {'\0'};
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int connfd;
    if ((connfd = accept(listenFd, (struct sockaddr*) &cliaddr, &clilen)) < 0 ) {
        printErrorMsg("accept");
    }

    memset(connIP, '\0', 32);
    strcpy(connIP, inet_ntoa(cliaddr.sin_addr));
    printf("connect IP: %s ------ Port: %d\n", connIP, ntohs(cliaddr.sin_port));

    //将新连接的文件描述符加入到clienArray
    Epoll::EventCallBack fun = std::bind(clientRcb, connfd, *epoll, dataStructer);
    epoll->addNewFd(connfd, fun);
}