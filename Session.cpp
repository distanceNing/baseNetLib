//
// Created by yangning on 18-1-14.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Session.h"
using namespace rapidjson;

static const char* begin = "BEGIN";
static const char* end = "END";

void Session::handleRequest(net::TcpConnection& connection, net::SocketBuf* buf)
{
    if(!parse(buf))
        return;
    //至此协议解析成功
    //下面做业务逻辑的处理
    process();

    //回复客户端处理结果
    std::string reply(Protocol::jsonObjToString(replyJson_));
    connection.sendInLoop(reply);
}

void Session::process() {
    Value::ConstMemberIterator itr = json->FindMember("cmd");
    if (itr == json->MemberEnd())
        return ;
    int cmd_type=atoi(itr->value.GetString());
    switch (cmd_type)
    {
    case kCmdRegister:break;
    case kCmdLogin:break;
    case kCmdAck:
        break;
    case kCmdDownload:break;
    case kCmdReTrans:break;
    case kCmdUpload:break;
    case kCmdUpdatePath:break;
    case kCmdContinue:break;
    case kCmdLogout:break;
    default:
        break;
    }

}
bool Session::parse(net::SocketBuf* buf)
{
    if(buf->readableBytes() <= 8)
    {
        //接收到的数据太少,返回等待下次数据到达
        return false;
    }
    const char* str= buf->readBegin();
    size_t len =buf->readableBytes();
    if(strncmp(str,begin,strlen(begin))!= 0 )
    {
        //数据块错误没有包含BEGIN
        return false;
    }

    const char* flag=std::search(str+strlen(begin),str+len,end,end+3);
    if(flag ==str+len)
    {
        //接收到的数据中没有END
        return false;
    }

    std::string json_str(str + strlen(begin),flag);

    json = Protocol::stringToJsonObj(json_str);

    return true;
}
