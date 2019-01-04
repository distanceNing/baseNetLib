//
// Created by yangning on 19-1-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "ConsumerList.h"
#include "../proto/Protocol.h"
ConsumerList ConsumerList::sConsumerList;
void ConsumerList::pushmsg2Consumter(std::map<std::string, std::string>& json_map)
{
    auto it = json_map.find("cmd");
    if(it != json_map.end()){
        json_map.erase(it);
    }
    auto msg_str = map2jsonstr(json_map);
    int type = atoi(json_map["msg_type"].c_str());

    auto ite = consumerList_.begin();
    for (; ite != consumerList_.end(); ++ite) {
        if(ite->second.getSubscribeMsgType() == type){
            ite->first->sendInLoop(msg_str);
        }
    }

}
bool ConsumerList::removeConsumer(net::TcpConnectionPtr& conn)
{
    auto ite = consumerList_.find(conn);
    if(ite != consumerList_.end()){
        consumerList_.erase(ite);
    }
    return true;
}
bool ConsumerList::addConsumer(net::TcpConnectionPtr& conn, Consumer consumer)
{
    auto ite = consumerList_.insert(std::make_pair(conn,consumer));
    return ite.second;
}
