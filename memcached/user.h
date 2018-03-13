//
// Created by yangning on 17-12-4.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_USER_H
#define MEMCACHED_USER_H
#include "mem_request.h"
#include "mem_response.h"



class DataStructer;
class User {
public:
    User(DataStructer* date_structer)
            :response_(date_structer)
    {
    }

    PARSE_RESULT handleRquest(net::SocketBuf& buf);

    REQ_TYPE getRequestType()
    {
        return request_.getRequestType();
    }
    void packResponse(PARSE_RESULT result);

    const size_t getResponseLength()
    {
        return response_.getResponseLength();
    }
    const char* getResponse() const
    {
        return response_.getResponse();
    }

    ~User()
    {
    }

private:
    Request request_;
    Response response_;
};

#endif //MEMCACHED_USER_H
