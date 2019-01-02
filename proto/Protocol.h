//
// Created by yangning on 18-1-11.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef THEAPP_PROTOCOL_H
#define THEAPP_PROTOCOL_H
#include <string>
#include <memory>
#include "rapidjson/document.h"// rapidjson's DOM-style API

class Protocol {
public:
    Protocol()
    {
    }

    static std::shared_ptr<rapidjson::Document> stringToJsonObj(const char* json_str);

    static std::shared_ptr<rapidjson::Document> stringToJsonObj(const std::string& json_str);

    static std::string jsonObjToString(const rapidjson::Document& json);



    ~Protocol()
    {
    }

private:
};

#endif //THEAPP_PROTOCOL_H
