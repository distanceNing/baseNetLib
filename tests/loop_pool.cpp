//
// Created by yangning on 18-3-27.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//
#include "gtest/gtest.h"
#include "../EventLoopThreadPool.h"

class TestLoopPool : public ::testing::TestWithParam<std::string> {
public:
    TestLoopPool()
            :response(&dataStructer_)
    {
    }

protected:
    //第一个case执行前执行
    static void SetUpTestCase()
    {
        //std::cout << "before test case\n";

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
    }

};

//TEST_F(TestResponse,)
