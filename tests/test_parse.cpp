#include <iostream>
#include "Request.h"
#include "socket/socket_buf.h"
#include "data_structer.h"

int main()
{

    net::SocketBuf buf;
    buf.append("set yn 32 1023434 8 \r\n");
    //buf.append("get yn\r\n");
    Request request;
    request.parse(buf);

    buf.append("yangning\r\n");



    buf.append("append ");


    buf.append("delete yn\r\n");
    return 0;
}