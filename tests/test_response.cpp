#include "gtest/gtest.h"
#include "../mem_response.h"
#include "../data_structer.h"

class TestResponse : public ::testing::TestWithParam<std::string> {
public:
    TestResponse()
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
    DataStructer dataStructer_;
    Response response;
};

//TEST_F(TestResponse,)