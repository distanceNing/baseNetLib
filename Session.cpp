//
// Created by yangning on 17-12-4.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "Session.h"
PARSE_RESULT User::handleRquest(net::SocketBuf& buf)
{
    PARSE_RESULT handle_res = request_.parse(buf);
    if ( handle_res != NOT_ALL && handle_res != NEED_DATA_BLOCK )
        request_.resetParseStat();
    return handle_res;
}
void User::packResponse()
{
    switch (request_.getRequestType()) {
    case REQ_SET: {
        response_.handleSet(request_.getKey(), request_.getValueInfo());
        break;
    }
    case REQ_GET: {
        response_.handleGet(request_.getKey(),request_.getKeyCount());
        break;
    }
    case REQ_DELETE: {
        response_.handleDelete(request_.getKey());
        break;
    }
    case REQ_FAIL: {
        response_.hanleBadReq();
        break;
    }
    case UNKNOWN_REQ: {
        response_.hanleBadReq();
        break;
    }
    default:break;

    }
}
