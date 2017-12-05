//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_REQUEST_H
#define MEMCACHED_REQUEST_H
#include "net/common.h"
#include "data_structer.h"

#include <string>

namespace net {
class SocketBuf;
};
enum REQ_TYPE {
  //storage
          REQ_SET = 1, REQ_ADD, REQ_REPLACE, REQ_APPEND, REQ_PREPEND,
  //get
          REQ_GET, REQ_GETS,
  //delete
          REQ_DELETE, REQ_QUIT,
          REQ_FLUSH_ALL,
  UNKNOWN_REQ,
};

enum PARSE_RESULT {
  NOT_PARSING = 100,NOT_ALL, PARSE_OK, BAD_REQ,NEED_DATA_BLOCK,
};
class Request {
public:
    Request()
            :isNoReplay(false), valueInfo_(new ValueInfo),currenParseStat_(NOT_PARSING),keyCount_(0)
    { }

    int parse(net::SocketBuf& socketBuf_);

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
    int pareseBody(char* begin);

    int parseSet(char* begin);

    int parseGet(char* begin);

    bool needDataBlock(){
        return requestType_ <= REQ_PREPEND;
    }

    PARSE_RESULT currenParseStat_;
    REQ_TYPE requestType_;
    ValueInfo* valueInfo_;
    std::string key_;
public:
    uint32_t getKeyCount() const;
private:
    uint32_t keyCount_;
    bool isNoReplay;

};

#endif //MEMCACHED_REQUEST_H
