//
// Created by yangning on 17-10-24.
//

#include "tcp_server.h"
#include "tcp_connection.h"
namespace net {
TcpServer::TcpServer(unsigned listen_port, EventLoop* loop)
        :serverLoop_(loop), acceptor_(new Acceptor(listen_port, serverLoop_))
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

void TcpServer::removeConnection(TcpConnection& connection)
{
    //先执行客户回调
    closeCallBack_(connection);
    //处理连接断开事件
    connection.handleClose();
    //从connections中删除连接
    auto ite = connectionMap_.find(connection.getFd());
    connectionMap_.erase(ite);

}
void TcpServer::newConnectionCallBack(int fd, IpAddress ip_address)
{
    TcpConnectionPtr con_ptr(new TcpConnection(fd, ip_address, serverLoop_));
    //设置连接client的事件回调函数
    con_ptr->setClienReadCallBack(clienReadCallBack_);
    con_ptr->setClienCloseCallBack(std::bind(&TcpServer::removeConnection, this, _1));
    con_ptr->setClienErrorCallBack(errorCallBack_);

    connectionMap_.insert(std::make_pair(fd,con_ptr));
    //connectionMap_[fd] = con_ptr;
}

} //namespace net