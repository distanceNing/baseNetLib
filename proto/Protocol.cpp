//
// Created by yangning on 18-1-11.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include <memory>
#include "Protocol.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/error/en.h"

using namespace rapidjson;
#include "common.h"

const char* Protocol::kSuccess = "Success";
const char* Protocol::kFail = "Fail";


std::shared_ptr<rapidjson::Document> Protocol::stringToJsonObj(const std::string& json_str)
{
    return stringToJsonObj(json_str.c_str());
}

std::shared_ptr<rapidjson::Document> Protocol::stringToJsonObj(const char* json_str)
{
    std::shared_ptr<rapidjson::Document> document(new rapidjson::Document);  // Default template parameter uses UTF8 and MemoryPoolAllocator.

#if 0
    // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
    assert(document.Parse(json).HasParseError());
#else
    // In-situ parsing, decode strings directly in the source string. Source must be string.
    char buffer[sizeof(json_str)];
    memcpy(buffer, json_str, sizeof(json_str));
    assert(document->ParseInsitu(buffer).HasParseError());
#endif
    return document;
}
std::string Protocol::jsonObjToString(const rapidjson::Document& json)
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    json.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    //适应咱们自身的协议加上头部BEGIN和尾部END
    char buffer[MAX_BUF_SIZE]={'\0'};
    snprintf(buffer,MAX_BUF_SIZE,"BEGIN%sEND",sb.GetString());
    return std::string(buffer);
}

std::string map2jsonstr(const std::map<std::string, std::string>& map)
{
    std::unique_ptr<rapidjson::Document> ptr_doc(new rapidjson::Document());
    ptr_doc->Parse("{}");
    rapidjson::Document::AllocatorType& allocator = ptr_doc->GetAllocator();


    for(const auto& ite : map){
        rapidjson::Value val(rapidjson::kObjectType);
        val.SetString(ite.second.c_str(), static_cast<rapidjson::SizeType>(ite.second.length()), ptr_doc->GetAllocator());;
        ptr_doc->AddMember(rapidjson::Value(ite.first.c_str(),allocator), val, allocator);//对象添加
    }

    return Protocol::jsonObjToString(*ptr_doc);
}

void jsonstr2map(std::map<std::string, std::string>& map, const char* json_str)
{
    if(!json_str)
        return;
    rapidjson::Document document(rapidjson::kObjectType);  // Default template parameter uses UTF8 and MemoryPoolAllocator.

    document.Parse(json_str); // 解析，Parse()无返回值，也不会抛异常
    if (document.HasParseError()) // 通过HasParseError()来判断解析是否成功
    {
        printf("parse error: (%d:%d) \n %s"
                "\n", document.GetParseError(), document.GetErrorOffset(),rapidjson::GetParseError_En(document.GetParseError()));
        return ;
    }
    assert(document.IsObject());
    auto ite = document.MemberBegin();
    for (ite; ite != document.MemberEnd(); ++ite) {
        const char* name = ite->name.GetString();
        const char* value = ite->value.GetString();
        map[name] = value;
    }
}
