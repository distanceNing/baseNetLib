//
// Created by yangning on 18-1-14.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//
const char json[] = "BEGIN{ \"cmd\" : 1,\"cmd_info\" : \"hello\"}END";

#include "gtest/gtest.h"
#include "Session.h"
class TestSession : public ::testing::Test {
protected:
    //第一个case执行前执行
    static void SetUpTestCase()
    {

    }
    //SetUp()方法在每个TestCase之前执行
    virtual void SetUp()
    {

    }
    // TearDown()方法在每个TestCase之后执行
    virtual void TearDown()
    {
    }
    static void TearDownTestCase()
    {
        // std::cout << "after test case\n";
    }

    net::SocketBuf buf_;
    Session session_;
};
TEST_F(TestSession,parse)
{
    buf_.append(json);
    session_.parse(&buf_);
    buf_.resetBuffer();
    buf_.append("BEGINEND");
    session_.parse(&buf_);
}