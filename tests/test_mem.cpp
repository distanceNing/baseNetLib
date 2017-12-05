#include "net/socket/tcp_socket.h"
#include "net/common.h"
#include "mem_request.h"
#include "mem_response.h"

static bool isLooping = true;

int main(int argc, char* argv[])
{
    net::TcpSocket listen_sock;
    if ( !listen_sock.CreateSocket(kPort))
        printErrorMsg("crete socket");
    listen_sock.Listen();
    printf("memcached is running on %d \n", kPort);
    DataStructer dataStructer;

    return 0;
}

void clientRcb(int fd, DataStructer* dataStructer)
{
    net::SocketBuf read_buf;
    ssize_t read_size = 0;
    ssize_t size;
    while ((size = read_buf.readFromFd(fd)) > 0) {
        read_size += size;
    }
    if ( read_size == 0 ) {

        close(fd);
        std::cout << "client fd " << fd << " close --\n";
    }
    else {
        Request request;
        if ( request.parse(read_buf) == PARSE_OK ) {
            if ( request.getRequestType() == REQ_QUIT ) {

                //关闭client socket
                close(fd);
                std::cout << "client fd " << fd << " close --\n";
            }
            else {
                mem_response response(dataStructer);
                switch (request.getRequestType()) {
                case REQ_SET: {
                    response.handleSet(request.getKey(), request.getValueInfo());
                    break;
                }
                case REQ_GET: {
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

void listenRcb(int listenFd,  DataStructer* dataStructer)
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

}