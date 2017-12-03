#include <iostream>
#include "Request.h"
#include "socket/socket_buf.h"

int main()
{
    std::cout << std::hash<const char*>()("yn") << std::endl;

    std::string sstr("yn");
    std::cout << std::hash<const char*>()(sstr.c_str()) << std::endl;
    const char* cstr = "yn";
    std::cout << std::hash<const char*>()(cstr) << std::endl;
    char* pstr = new char[3];
    strcpy(pstr, cstr);
    pstr[2] = 0;
    std::cout << std::hash<const char*>()(pstr) << std::endl;

    std::string str1("yn");
    std::string str2 = str1;
    std::string str3(cstr);
    std::string str4 = "yn";
    std::cout << std::hash<const char*>()(str1.c_str()) << std::endl;
    std::cout << std::hash<const char*>()(str2.c_str()) << std::endl;
    std::cout << std::hash<const char*>()(str3.c_str()) << std::endl;

    std::cout << std::hash<std::string>()(str1) << std::endl;
    std::cout << std::hash<std::string>()(str2) << std::endl;
    std::cout << std::hash<std::string>()(str3) << std::endl;
    std::cout << std::hash<std::string>()(str4) << std::endl;
    std::cout << std::hash<std::string>()(std::string("yn")) << std::endl;
    return 0;
}