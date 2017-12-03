//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//
#include "Request.h"
#include "socket/socket_buf.h"
#include "common.h"
#include "data_structer.h"

#define SKIP_SPACE(ptr) do\
{\
for (;*ptr == ' '||*ptr=='\n';++ptr)\
;\
}while (0)

PARSE_RESULT Request::parse()
{
    char* crlf = socketBuf_.findCRLF();
    if ( crlf == NULL )
        return NOT_ALL;
    *crlf = '\0';
    char* begin = socketBuf_.readBegin();
    socketBuf_.skip(strlen(begin) + 2);
    begin = pareseType(begin);
    SKIP_SPACE(begin);
    pareseBody(begin);
    valueInfo_->value_ = new char[valueInfo_->value_len_];
    socketBuf_.read(valueInfo_->value_, valueInfo_->value_len_);
    return PARSE_OK;
}

PARSE_RESULT Request::pareseBody(char* begin)
{
    switch (requestType_) {
    case SET: {
        char* flag = std::find(begin, begin + strlen(begin), ' ');
        *flag++ = '\0';
        key_ = begin;
        char* exptiem = strpbrk(flag, " \t");
        *exptiem++ = '\0';
        valueInfo_->flags_ = (uint32_t) atoi(flag);
        char* bytes = strpbrk(exptiem, " \t");
        *bytes++ = '\0';
        valueInfo_->exptime_ = atoi(exptiem);
        valueInfo_->value_len_ = (uint32_t) atoi(bytes);
        break;
    }
    case GET: {
        key_ = begin;
        break;
    }
    case GETS:break;

    case ADD:break;
    case REPLACE:break;
    case APPEND: {

        break;
    }
    case PREPEND:break;
    case DELETE: {
        key_ = begin;
        break;
    }
    case QUIT: {
        break;
    }
    default:break;

    }
    return PARSE_OK;
}

char* Request::pareseType(char* begin)
{
    if ( !strncmp(begin, "set", 3)) {
        requestType_ = SET;
        return begin += 3;
    }
    else if ( !strncmp(begin, "add", 3)) {
        requestType_ = ADD;
        return begin += 3;
    }
    else if ( !strncmp(begin, "replace", 7)) {
        requestType_ = REPLACE;
        return begin += 7;
    }
    else if ( !strncmp(begin, "append", 6)) {
        requestType_ = APPEND;
        return begin += 6;
    }
    else if ( !strncmp(begin, "prepend", 7)) {
        requestType_ = PREPEND;
        return begin += 7;
    }
    else if ( !strncmp(begin, "get", 3)) {
        requestType_ = GET;
        return begin += 3;
    }
    else if ( !strncmp(begin, "gets", 4)) {
        requestType_ = GETS;
        return begin += 4;
    }
    else if ( !strncmp(begin, "delete", 6)) {
        requestType_ = DELETE;
        return begin += 6;
    }
    else if ( !strncmp(begin, "quit", 4)) {
        requestType_ = QUIT;
        return begin += 4;
    }

}

REQ_TYPE Request::getRequestType() const
{
    return requestType_;
}
const std::string& Request::getKey() const
{
    return key_;
}



