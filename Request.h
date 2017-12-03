//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_REQUEST_H
#define MEMCACHED_REQUEST_H
#include "common.h"
#include "data_structer.h"

#include <string>
namespace net {
class SocketBuf;
};
enum REQ_TYPE {
  //storage
          SET = 1, ADD, REPLACE, APPEND, PREPEND, //get
          GET, GETS, //delete
          DELETE, QUIT,
};

enum PARSE_RESULT {
  NOT_ALL, PARSE_OK, BAD_REQ,
};
class Request {
public:
    Request(net::SocketBuf& sock_buf)
            :isNoReplay(false), socketBuf_(sock_buf), valueInfo_(new ValueInfo)
    {
    }
    PARSE_RESULT parse();

    const std::string& getKey() const;

    REQ_TYPE getRequestType() const;

    inline ValueInfo* getValueInfo()
    {
        return valueInfo_;
    }

    ~Request()
    {
    }

private:
    char* pareseType(char* begin);
    PARSE_RESULT pareseBody(char* begin);
    net::SocketBuf& socketBuf_;
    REQ_TYPE requestType_;
    ValueInfo* valueInfo_;
    std::string key_;
    bool isNoReplay;

};

#endif //MEMCACHED_REQUEST_H
