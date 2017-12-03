//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_RESPONSE_H
#define MEMCACHED_RESPONSE_H

#include <string>
class DataStructer;
struct ValueInfo;
class Response {
public:
    Response(DataStructer* dataStructer)
            :dataStructer_(dataStructer)
    {
    }
    ~Response()
    {
    }

    void handleGet(const std::string& key);

    void handleSet(const std::string& key, ValueInfo* value_info);
public:
    const size_t getResponseLength()
    {
        return response_.size();
    }
    const char* getResponse() const
    {
        return response_.c_str();
    }
private:
    std::string response_;
    DataStructer* dataStructer_;
};

#endif //MEMCACHED_RESPONSE_H
