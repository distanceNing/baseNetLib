//
// Created by yangning on 18-1-17.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef HOMEWORK_SCOPEGUARD_H
#define HOMEWORK_SCOPEGUARD_H

#include <functional>
#include <boost/noncopyable.hpp>

using ExitHandle =std::function<void()>;

class ScopeGuard:private boost::noncopyable {
public:
    ScopeGuard(ExitHandle exit_handle):exitHandle_(exit_handle)
    {
    }

    ~ScopeGuard()
    {
        if(exitHandle_)
            exitHandle_();
    }

private:
    ExitHandle exitHandle_;
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line

#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)


#define ON_SCOPE_EXIT(exit_handle) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(exit_handle)


#endif //HOMEWORK_SCOPEGUARD_H
