//
// Created by yangning on 18-1-14.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//
#include "msg/MsgFactory.h"
#include "Session.h"
#include "proto/Protocol.h"
#include "consumer/ConsumerList.h"
using namespace rapidjson;

static const char* begin = "BEGIN";
static const char* end = "END";

void Session::handleRequest(net::TcpConnectionPtr& connection, net::SocketBuf* buf)
{
    auto json = parse(buf);
    if ( json.empty() )
        return;
    //至此协议解析成功
    //下面做业务逻辑的处理
    auto reply_info = process(json,connection);

    //回复客户端处理结果
    connection->sendInLoop(reply_info);
}

std::string Session::process(const std::string& json,net::TcpConnectionPtr& connection)
{
    std::map<std::string,std::string> map;
    jsonstr2map(map,json.c_str());
    std::string reply_info("");
    auto itr = map.find("cmd");
    if ( itr == map.end())
        return NULL;
    int cmd_type = atoi(itr->second.c_str());

    switch (cmd_type) {
    case Protocol::kCmdRegister: {
        int type = atoi(map["msg_type"].c_str());
        reply_info = handleRegister(connection,type) ? Protocol::kSuccess : Protocol::kFail;
        break;
    }
    case Protocol::kCmdPush: {
        int proto = atoi(map["msg_proto"].c_str());
        int type = atoi(map["msg_type"].c_str());
        std::string str = map["content"];
        reply_info = handlePushMsg(type, proto, str) ? Protocol::kSuccess : Protocol::kFail;
        push2Consumer(map);
        break;
    }
    default:break;
    }
    return reply_info;

}
std::string Session::parse(net::SocketBuf* buf)
{
    if ( buf->readableBytes() <= 8 ) {
        //接收到的数据太少,返回等待下次数据到达
        return "";
    }
    const char* str = buf->readBegin();
    size_t len = buf->readableBytes();
    if ( strncmp(str, begin, strlen(begin)) != 0 ) {
        //数据块错误没有包含BEGIN
        return "";
    }

    const char* flag = std::search(str + strlen(begin), str + len, end, end + 3);
    if ( flag == str + len ) {
        //接收到的数据中没有END
        return "";
    }

    std::string json_str(str + strlen(begin), flag);

    //auto json = Protocol::stringToJsonObj(json_str);
    buf->skip(len);
    return json_str;
}
bool Session::handleRegister(net::TcpConnectionPtr& connection,int type)
{
    Consumer consumer(type);
    ConsumerList::getInstence().addConsumer(connection,consumer);
    return true;
}

bool Session::handlePushMsg(int type, int proto, const std::string& content)
{//构建一个消息对象,将这个对象push到全局的数据结构中



    /*switch (type) {
    case Protocol::kAnnounceMsg : {
        std::shared_ptr<Msg> msg(new AnnounceMsg(content));
        msg->setMsgType(proto);
        msgSet_.insert(msg);
        break;
    }
    case Protocol::kInfoMsg: {
        std::shared_ptr<Msg> infomsg(new InfoMsg(content));
        infomsg->setMsgType(proto);
        msgSet_.insert(infomsg);
        break;
    }
    case Protocol::kRemindMsg: {
        std::shared_ptr<Msg> remindmsg(new InfoMsg(content));
        remindmsg->setMsgType(proto);
        msgSet_.insert(remindmsg);
        break;
    }
    default:break;
    }*/
    return true;
}
bool Session::push2Consumer(std::map<std::string, std::string>& json_map)
{
    ConsumerList::getInstence().pushmsg2Consumter(json_map);
    return false;
}
