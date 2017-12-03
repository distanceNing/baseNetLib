#include <iostream>
#include "data_structer.h"

int main()
{
    ValueInfo* valueInfo = new ValueInfo;
    valueInfo->cas_ = 0;
    valueInfo->flags_ = 0;
    valueInfo->exptime_ = 0;
    valueInfo->value_len_ = 5;
    valueInfo->setValue("yn001", valueInfo->value_len_);

    DataStructer dataStructer;
    dataStructer.insert("yn", valueInfo);
    dataStructer.append("yn", "hello world", 11);
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
}//

