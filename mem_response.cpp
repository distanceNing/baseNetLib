//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "mem_response.h"
#include "data_structer.h"

static const char* NOT_FOUND = "NOT_FOUND";
static const char* STORED = "STORED";
static const char* NOT_STORED = "NOT_STORED";
static const char* EXISTED = "EXISTED";
static const char* DELETED = "DELETED";
static const char* ERROR = "ERROR";
static const char* UNKNOWN = "UNKNOWN";
static const char* CLIENT_ERROR = "CLIENT_ERROR: ";
static const char* END = "END";
static const char* CRLF = "\r\n";

void Response::handleGet(const std::string& keys, const uint32_t key_count)
{
    size_t pos = 0;
    std::string key("");
    size_t dis = 0;
    response_ = "";
    for (int i = 0; i < key_count; ++i) {
        dis = key.size() == 0 ? 0 : key.size() + 2 + dis;
        pos = keys.find("\r\n", pos);
        key = keys.substr(dis, pos - dis);
        pos += 2;
        const ValueInfo* value_info = dataStructer_->getValue(key);
        if ( value_info != nullptr )
            response_ += std::move(value_info->packInfo(key));
        else {
            response_ += key;
            response_ += CRLF;
            response_ += NOT_FOUND;
        }
        response_ += CRLF;
    }
}

void Response::handleSet(const std::string& key, ValueInfo* value_info)
{
    assert(value_info != NULL);
    DataStructer::OperatorRes res = dataStructer_->insert(key, value_info);
    if ( res == DataStructer::kOperatorOk )
        response_ = STORED;
    else if ( res == DataStructer::kExisted )
        response_ = EXISTED;
    else if ( res == DataStructer::kOperatorFail )
        response_ = NOT_STORED;
    response_ += CRLF;
}

void Response::handleDelete(const std::string& key)
{
    DataStructer::OperatorRes res = dataStructer_->remove(key);
    if ( res == DataStructer::kOperatorOk )
        response_ = DELETED;
    else if ( res == DataStructer::kNotFound )
        response_ = NOT_FOUND;
    else if ( res == DataStructer::kOperatorFail )
        response_ = ERROR;
    response_ += CRLF;
}

void Response::hanleBadReq()
{
    response_ = ERROR;
    response_ += CRLF;
}

void Response::badDataBlock(PARSE_RESULT result)
{
    response_ = CLIENT_ERROR;
    if ( result == DATA_BLOCK_LONG ) {
        response_ += "bad data block too long";

    }
    else if ( result == DATA_BLOCK_SHORT ) {
        response_ += "bad data block too short";
    }
    response_ += CRLF;
}

void Response::handleUnknown()
{
    response_ = UNKNOWN;
    response_ += CRLF;
}
