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
static const char* DELETED = "DELETED";
static const char* ERROR = "ERROR";
static const char* END = "END";
static const char* CRLF = "\r\n";


void Response::handleGet(const std::string& key)
{
    const ValueInfo* value_info = dataStructer_->getValue(key);
    if ( value_info != nullptr )
        response_ = std::move(value_info->packInfo(key));
    else {
        response_ = NOT_FOUND;
    }
    response_ += CRLF;
}

void Response::handleSet(const std::string& key, ValueInfo* value_info)
{
    assert(value_info != NULL);
    if ( dataStructer_->insert(key, value_info))
        response_ = STORED;
    else
        response_ = NOT_STORED;
    response_+=CRLF;
}

void Response::handleDelete(const std::string& key)
{
    if(dataStructer_->remove(key))
        response_=DELETED;
    else
        response_=NOT_FOUND;
    response_+=CRLF;
}
void Response::hanleBadReq()
{
    response_=ERROR;
    response_+=CRLF;
}
