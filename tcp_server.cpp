//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"
#include "tcp_connection.h"
#include "event_loop.h"
#include "EventLoopThreadPool.h"
using namespace std::placeholders;

namespace net {
TcpServer::TcpServer(unsigned listen_port, EventLoop* loop,size_t thread_num)
        :serverLoop_(loop), acceptor_(new Acceptor(listen_port, serverLoop_)),loopPool_(new EventLoopThreadPool(loop,thread_num))
{
    acceptor_->setNewConnetcionCallBack(std::bind(&TcpServer::newConnectionCallBack, this, _1, _2));
}

void TcpServer::serverStart()
{
    acceptor_->listen();
    serverLoop_->startLoop();
}

void TcpServer::serverStop()
{
    serverLoop_->quitLoop();
}

void TcpServer::removeConnection(TcpConnectionPtr connection)
{
    //先执行客户回调
    if(closeCallBack_)
        closeCallBack_(connection);
    //从connections中删除连接
    connectionMap_.erase(connection->getFd());

    serverLoop_->addTaskInQueue(std::bind(&TcpConnection::destoryConn,connection));
}
void TcpServer::newConnectionCallBack(int fd, const IpAddress& ip_address)
{
    EventLoop* ioloop = loopPool_->getNextLoop();
    TcpConnectionPtr con_ptr(new TcpConnection(fd, ip_address, ioloop));
    //设置连接client的事件回调函数
    con_ptr->setClienReadCallBack(clienReadCallBack_);
    con_ptr->setClienCloseCallBack(std::bind(&TcpServer::removeConnection, this, _1));
    con_ptr->setClienErrorCallBack(errorCallBack_);

    connectionMap_.insert(std::make_pair(fd,con_ptr));
    //connectionMap_[fd] = con_ptr;
    if(newConnCallBack_)
        newConnCallBack_(fd,ip_address);

    ioloop->runInLoop(std::bind(&TcpConnection::enableConnection,con_ptr));
}

} //namespace net