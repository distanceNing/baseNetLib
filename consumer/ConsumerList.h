//
// Created by yangning on 19-1-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_CONSUMERLIST_H
#define BASE_NET_LIB_CONSUMERLIST_H
#include "../tcp_connection.h"
#include "consumer.h"
class ConsumerList {
public:

    bool addConsumer(net::TcpConnectionPtr& conn,Consumer consumer);

    bool removeConsumer(net::TcpConnectionPtr& conn);


    void pushmsg2Consumter(std::map<std::string,std::string>& json_map);

    static ConsumerList& getInstence(){
        return sConsumerList;
    }

    ~ConsumerList()
    {
    }
private:
    static ConsumerList sConsumerList;
    ConsumerList()
    {
    }

    std::map<net::TcpConnectionPtr,Consumer> consumerList_;
};

#endif //BASE_NET_LIB_CONSUMERLIST_H
