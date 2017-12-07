#include "gtest/gtest.h"
#include "../net/socket/socket_buf.h"
#include "../mem_request.h"
#include "../data_structer.h"
#include "../mem_response.h"

#define TEST_GET(buf, str, result, key_num) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    Request request;\
    EXPECT_EQ(result,request.parse(buf));\
    EXPECT_EQ(key_num,request.getKeyCount());\
}while(0)
//加入参数
class GetTest : public ::testing::TestWithParam<std::string >{
public:
    //第一个case执行前执行
    static void SetUpTestCase()
    {
        std::cout << "before test case\n";

    }
    //SetUp()方法在每个TestCase之前执行
    virtual void SetUp()
    {
        //std::cout<<GetParam()<<std::endl;
    }
    // TearDown()方法在每个TestCase之后执行
    virtual void TearDown()
    {
        //m_foo.Finalize();
    }
    //最后一个case执行完后执行
    static void TearDownTestCase()
    {
        std::cout << "after test case\n";
    }
    // Some expensive resource shared by all tests.

    net::SocketBuf buf;
};
INSTANTIATE_TEST_CASE_P(TrueReturn, GetTest, testing::Values("get\r\n","get \r\n","get   \r\n"));
TEST_P(GetTest, bad_req)
{
   std::string str =  GetParam();
    TEST_GET(buf, str, BAD_REQ, 0);
}

TEST_F(GetTest, req_get)
{
    TEST_GET(buf, "get \r\n", BAD_REQ, 0);
    TEST_GET(buf, "get", NOT_ALL, 0);
    TEST_GET(buf, "g\r\n", PARSE_UNKNOWN_REQ, 0);

}



#define TEST_REQ_TYPE(request, buf, str, result) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    request.parse(buf);\
    EXPECT_EQ(result,request.getRequestType());\
}while(0)

#define APEND_BUF(buf, str, result) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    Request request;\
    EXPECT_EQ(result,request.parse(buf));\
}while(0)

TEST(request, test_req_type)
{
    Request request;
    net::SocketBuf buf;
    //TEST_REQ_TYPE(request,buf,"set a 1 1 1\r\n",REQ_SET);
    request.resetParseStat();
    TEST_REQ_TYPE(request, buf, "get yn\r\n", REQ_GET);
    request.resetParseStat();
    TEST_REQ_TYPE(request, buf, "delete\r\n", REQ_FAIL);
    request.resetParseStat();
    TEST_REQ_TYPE(request, buf, "quit\r\n", REQ_QUIT);
    request.resetParseStat();
    TEST_REQ_TYPE(request, buf, "delete yn\r\n", REQ_DELETE);

}
TEST(req, req_set)
{
    net::SocketBuf buf;
    APEND_BUF(buf, "set yn 32 1023434 8\r\n", NEED_DATA_BLOCK);
    APEND_BUF(buf, "set yn 32 102343", NOT_ALL);
    APEND_BUF(buf, "set yn 32 1023434 8\r\n yn\r\n", PARSE_OK);
    APEND_BUF(buf, "set yn 32 1023434 8\r\n yn", NEED_DATA_BLOCK);

    APEND_BUF(buf, "set   \r\n yn", BAD_REQ);
    APEND_BUF(buf, "set yn  \r\n yn", BAD_REQ);
    APEND_BUF(buf, "set yn 32 \r\n yn", BAD_REQ);
    APEND_BUF(buf, "set yn 32 1023434  \r\n yn", BAD_REQ);

    APEND_BUF(buf, "set yn a \r\n yn", BAD_REQ);
    APEND_BUF(buf, "set yn 32 a\r\n yn", BAD_REQ);
    APEND_BUF(buf, "set yn 32 32 a\r\n yn", BAD_REQ);
}
TEST(req, req_get)
{
    net::SocketBuf buf;
    TEST_GET(buf, "get \r\n", BAD_REQ, 0);
    TEST_GET(buf, "get", NOT_ALL, 0);
    TEST_GET(buf, "g\r\n", PARSE_UNKNOWN_REQ, 0);

    TEST_GET(buf, "get yn\r\n", PARSE_OK, 1);
    TEST_GET(buf, "get yn yn1\r\n", PARSE_OK, 2);
    TEST_GET(buf, "get yn yn1 yn2\r\n", PARSE_OK, 3);
    TEST_GET(buf, "get yn \r\n", PARSE_OK, 1);
    TEST_GET(buf, "get yn yn1 \r\n", PARSE_OK, 2);
}
TEST(req, req_delete)
{
    net::SocketBuf buf;
    APEND_BUF(buf, "delete \r\n", BAD_REQ);
    APEND_BUF(buf, "delete yn\r\n", PARSE_OK);
    APEND_BUF(buf, "delete", NOT_ALL);
    APEND_BUF(buf, "de\r\n", PARSE_UNKNOWN_REQ);
}

