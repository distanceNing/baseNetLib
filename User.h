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
    ~User()
    {
    }

private:
    Request request_;
    Response response_;
};

#endif //MEMCACHED_USER_H
