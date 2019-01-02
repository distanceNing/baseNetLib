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


using namespace rapidjson;
#include "common.h"




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
