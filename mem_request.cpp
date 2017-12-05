//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//
#include "request.h"
#include "socket/socket_buf.h"
#include "net/common.h"
#include "data_structer.h"

inline bool strIsNum(const char* flag)
{
    for (; *flag != '\0'; ++flag) {
        if ( *flag < '0' || *flag > '9' )
            return false;
    }
    return true;
}
static const char* FLUSH_ALL = "flash_all";
static const char* DELETE = "delete";
static const char* QUIT = "quit";

#define SKIP_SPACE(ptr) do\
{\
for (;*ptr == ' '||*ptr=='\n';++ptr)\
;\
}while (0)

int request::parse(net::SocketBuf& sock_buf)
{

    char* crlf = sock_buf.findCRLF();
    if ( crlf == NULL )
        currenParseStat_ = currenParseStat_ == NOT_PARSING ? NOT_ALL : currenParseStat_;
    else {
        char* begin = NULL;
        if ( currenParseStat_ == NOT_PARSING ) {
            *crlf = '\0';
            begin = sock_buf.readBegin();
            //数据读取了一行
            sock_buf.skip(strlen(begin) + 2);
            begin = pareseType(begin);
            if ( requestType_ == UNKNOWN_REQ )
                return UNKNOWN_REQ;

            if ( pareseBody(begin) == BAD_REQ ) {
                return BAD_REQ;
            }
            if ( needDataBlock()) {
                currenParseStat_ = NEED_DATA_BLOCK;
                crlf = sock_buf.findCRLF();
            }
            else
                currenParseStat_ = PARSE_OK;
        }
        if ( crlf != NULL && currenParseStat_ == NEED_DATA_BLOCK ) {
            valueInfo_->value_ = new char[valueInfo_->value_len_];
            sock_buf.read(valueInfo_->value_, valueInfo_->value_len_);
            currenParseStat_ = PARSE_OK;
        }
    }
    return currenParseStat_;
}

int request::pareseBody(char* begin)
{
    SKIP_SPACE(begin);
    if ( *begin == '\0' )
        return BAD_REQ;
    switch (requestType_) {
    case REQ_SET: {
        return parseSet(begin);
    }
    case REQ_GET: {
        return parseGet(begin);
    }
    case REQ_GETS:break;
    case REQ_ADD:break;
    case REQ_REPLACE:break;
    case REQ_APPEND: {

        break;
    }
    case REQ_PREPEND:break;
    case REQ_DELETE: {
        key_ = begin;
        break;
    }
    case REQ_FLUSH_ALL:break;
    case REQ_QUIT: {
        break;
    }
    default:break;

    }
    return PARSE_OK;
}

int request::parseSet(char* begin)
{

    char* flag = std::find(begin, begin + strlen(begin), ' ');
    if ( *flag == '\0' )
        return BAD_REQ;
    *flag++ = '\0';
    key_ = begin;

    char* exptiem = std::find(flag, flag + strlen(flag), ' ');
    if ( *exptiem == '\0' )
        return BAD_REQ;
    *exptiem++ = '\0';
    if ( !strIsNum(flag))
        return BAD_REQ;
    valueInfo_->flags_ = (uint32_t) atoi(flag);
    char* bytes = std::find(exptiem, exptiem + strlen(exptiem), ' ');
    if ( *bytes == '\0' )
        return BAD_REQ;
    *bytes++ = '\0';
    if ( !strIsNum(exptiem))
        return BAD_REQ;
    valueInfo_->exptime_ = atoi(exptiem);
    if ( !strIsNum(bytes))
        return BAD_REQ;
    valueInfo_->value_len_ = (uint32_t) atoi(bytes);
    return 0;
}

char* request::pareseType(char* begin)
{
    if ( !strncmp(begin, "set", 3)) {
        requestType_ = REQ_SET;
        return begin += 3;
    }
    else if ( !strncmp(begin, "add", 3)) {
        requestType_ = REQ_ADD;
        return begin += 3;
    }
    else if ( !strncmp(begin, "replace", 7)) {
        requestType_ = REQ_REPLACE;
        return begin += 7;
    }
    else if ( !strncmp(begin, "append", 6)) {
        requestType_ = REQ_APPEND;
        return begin += 6;
    }
    else if ( !strncmp(begin, "prepend", 7)) {
        requestType_ = REQ_PREPEND;
        return begin += 7;
    }
    else if ( !strncmp(begin, "get", 3)) {
        requestType_ = REQ_GET;
        return begin += 3;
    }
    else if ( !strncmp(begin, "gets", 4)) {
        requestType_ = REQ_GETS;
        return begin += 4;
    }
    else if ( !strncmp(begin, "delete", 6)) {
        requestType_ = REQ_DELETE;
        return begin += 6;
    }
    else if ( !strncmp(begin, "quit", 4)) {
        requestType_ = REQ_QUIT;
        return begin += 4;
    }
    else if ( !strncmp(begin, FLUSH_ALL, strlen(FLUSH_ALL))) {
        requestType_ = REQ_FLUSH_ALL;
        return begin += strlen(FLUSH_ALL);
    }
    else {
        requestType_ = UNKNOWN_REQ;
    }
    return NULL;
}

REQ_TYPE request::getRequestType() const
{
    return requestType_;
}
const std::string& request::getKey() const
{
    return key_;
}
int request::parseGet(char* begin)
{
    char* flag = NULL;
    keyCount_ = 0;
    while (*(flag = std::find(begin, begin + strlen(begin), ' ')) != '\0') {
        *flag++ = '\0';
        key_ += begin;
        key_ += "\r\n";
        begin = flag;
        ++keyCount_;
    }
    if(*begin != '\0')
    {
        key_ += begin;
        key_ += "\r\n";
        ++keyCount_;
    }
    return keyCount_ == 0 ?  BAD_REQ:PARSE_OK;
}
uint32_t request::getKeyCount()const
{
    return keyCount_;
}



