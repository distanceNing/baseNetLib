//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Response.h"
#include "data_structer.h"
void Response::handleGet(const std::string& key)
{
    const ValueInfo* value_info = dataStructer_->getValue(key);
    if ( value_info != nullptr )
        response_ = std::move(value_info->packInfo(key));
    else
        response_ = "NOT FOUND\r\n";

}
void Response::handleSet(const std::string& key, ValueInfo* value_info)
{
    assert(value_info != NULL);
    if ( dataStructer_->insert(key, value_info))
        response_ = "STORED\r\n";
    else
        response_ = "FAIL\r\n";
}
