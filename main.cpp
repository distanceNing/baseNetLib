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
    tcpServer.serNewConnCallBack(std::bind(&App::newUserConn,&app,_1,_2));
    tcpServer.setClienCloseCallBack(std::bind(&App::userCloseConn,&app,_1));

    tcpServer.serverStart();

    return 0;
}


