#include <iostream>
#include "Request.h"
#include "socket/socket_buf.h"
#include "data_structer.h"

int main()
{

    net::SocketBuf buf;
    buf.append("set yn 32 1023434 8 \r\nyangning");
    //buf.append("get yn\r\n");
    Request request(buf);
    request.parse();

    DataStructer dataStructer;
    dataStructer.insert(request.getKey().c_str(), request.getValueInfo());
    const char* key = "yn";
    if ( !dataStructer.append(key, "hello world", 11))
        std::cout << "append fail \n";
    const ValueInfo* temp = dataStructer.getValue("yn");
    if ( temp != nullptr )
        temp->printInfo();
    else
        std::cout << "NOT FOUND \n";
    temp = dataStructer.getValue("aa");
    if ( temp != nullptr )
        temp->printInfo();
    else
        std::cout << "NOT FOUND \n";

    dataStructer.remove("yn");
    temp = dataStructer.getValue("yn");
    if ( temp != nullptr )
        temp->printInfo();
    else
        std::cout << "NOT FOUND \n";

    return 0;
}