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
   REQ_FAIL,
};

enum PARSE_RESULT {
  NOT_PARSING = 100,NOT_ALL,NEED_DATA_BLOCK, PARSE_OK, BAD_REQ,PARSE_UNKNOWN_REQ,DATA_BLOCK_SHORT,DATA_BLOCK_LONG
};
class Request {
public:
    Request()
            :isNoReplay(false),currenParseStat_(NOT_PARSING),keyCount_(0)
    { }

    PARSE_RESULT parse(net::SocketBuf& socketBuf_);

    void resetParseStat()
    {
         currenParseStat_=NOT_PARSING;
    }
    const std::string& getKey() const;

    REQ_TYPE getRequestType() const;

    inline ValueInfo* getValueInfo()
    {
        return &valueInfo_;
    }
    PARSE_RESULT getParseResult()const
    {
        return currenParseStat_;
    }

    void fillValueInfo(const char* crlf,net::SocketBuf& sock_buf);

    ~Request()
    {
        if(valueInfo_.value_)
            delete []valueInfo_.value_;
    }

private:
    char* pareseType(char* begin);
    int pareseBody(char* begin);

    PARSE_RESULT parseSet(char* begin);

    PARSE_RESULT parseGet(char* begin);

    bool needDataBlock(){
        return requestType_ <= REQ_PREPEND;
    }


public:
    uint32_t getKeyCount() const;
private:
    PARSE_RESULT currenParseStat_;
    REQ_TYPE requestType_;
    ValueInfo valueInfo_;
    std::string key_;

    uint32_t keyCount_;
    bool isNoReplay;

};

#endif //MEMCACHED_REQUEST_H
