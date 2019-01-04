
#include "msg.h"

//#include "net/socket/tcp_socket.h"

#include "rapidjson/document.h"
#include "../proto/Protocol.h"

#include <iostream>
using namespace std;
void XML::subscribemessImp() {
	cout<<"以XML方式显示"<<endl;
}

void HTML::subscribemessImp() {
	cout<<"以HTML方式显示"<<endl;
}

void JSON::subscribemessImp() {
	cout<<"以JSON方式显示"<<endl;
}

void Msg::setMsgType(int msg_proto)
{
    msg_proto_num_ = msg_proto;
	switch (msg_proto)
	{
	case Protocol::kHtml:
        msg_proto_ = new HTML();
		break;
	case Protocol::kJson:
        msg_proto_ = new JSON();
		break;
	case Protocol::kXml:
        msg_proto_ = new XML();
		break;;
	default:
		break;
	}
}

std::string Msg::packMsg(const std::string& content)
{
    std::map<std::string,std::string> map;
    //map["cmd"] = std::to_string(Protocol::kCmdPush);
    map["msg_type"] = std::to_string(msg_type_);
    map["msg_proto"] = std::to_string(msg_proto_num_);
    map["content"] = content;

    auto str_msg = map2jsonstr(map);
    return str_msg;
}
