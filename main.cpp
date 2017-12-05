#include "app.h"
#include "net/event_loop.h"
#include "net/tcp_server.h"
#include "net/common.h"
static bool isLooping = true;

int main(int argc, char* argv[])
{
    net::EventLoop loop(net::POLL);
    net::TcpServer tcpServer(kPort,&loop);
    App app;
    tcpServer.setClientReadCallBack(std::bind(&App::userMessageCallBack,&app,_1,_2));
    tcpServer.serverStart();

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
                Response response(dataStructer);
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

