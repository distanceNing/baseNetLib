#include "gtest/gtest.h"
#include "../net/socket/socket_buf.h"
#include "../mem_request.h"

#define TEST_GET(buf, str, result, key_num) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    Request request;\
    EXPECT_EQ(result,request.parse(buf));\
    EXPECT_EQ(key_num,request.getKeyCount());\
}while(0)

#define TEST_REQ_TYPE(request, buf, str, result) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    request.parse(buf);\
    EXPECT_EQ(result,request.getRequestType());\
}while(0)

#define APEND_BUF(buf, request, str, result) \
do{\
    buf.resetBuffer();\
    buf.append(str);\
    EXPECT_EQ(result,request.parse(buf));\
}while(0)




//加入参数
class ReqTest : public ::testing::TestWithParam<std::string> {
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
    Request request;
    net::SocketBuf buf;
};
INSTANTIATE_TEST_CASE_P(TrueReturn, ReqTest, testing::Values("get\r\n", "get \r\n", "get   \r\n"));
TEST_P(ReqTest, bad_req)
{
    std::string str = GetParam();
    TEST_GET(buf, str, BAD_REQ, 0);
}

TEST_F(ReqTest, req_type_get)
{
    TEST_GET(buf, "get \r\n", BAD_REQ, 0);
    TEST_GET(buf, "get", NOT_ALL, 0);
    TEST_GET(buf, "g\r\n", PARSE_UNKNOWN_REQ, 0);

}

#define TEST_PARSE(buf, request, str, result) \
do{\
    buf.append(str);\
    EXPECT_EQ(result,request.parse(buf));\
}while(0)


TEST_F(ReqTest, req_set)
{
    buf.resetBuffer();
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 1023434 8\r\n", NEED_DATA_BLOCK);
    TEST_PARSE(buf, request, "setaaaaa\r\n", PARSE_OK);
    EXPECT_EQ((int)REQ_SET,request.getRequestType());
    request.resetParseStat();
    TEST_PARSE(buf, request, "quit\r\n", PARSE_OK);
    EXPECT_EQ(REQ_QUIT,request.getRequestType());
    TEST_PARSE(buf, request, "set yn 32 1023434 3\r\n yn\r\n", PARSE_OK);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 102343 1", NOT_ALL);
    TEST_PARSE(buf, request, "\r\n", NEED_DATA_BLOCK);
    TEST_PARSE(buf, request, "1\r\n", PARSE_OK);
    EXPECT_EQ((int)REQ_SET,request.getRequestType());
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 1023434 3\r\n yn\r\n", PARSE_OK);
    EXPECT_EQ((int)REQ_SET,request.getRequestType());
    request.resetParseStat();

    TEST_PARSE(buf, request, "set yn 32 1023434 4\r\n yn\r\n", DATA_BLOCK_SHORT);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 1023434 1\r\n yn\r\n", DATA_BLOCK_LONG);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set   \r\n yn", BAD_REQ);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn  \r\n yn", BAD_REQ);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 \r\n yn", BAD_REQ);
    request.resetParseStat();
    TEST_PARSE(buf, request, "set yn 32 1023434  \r\n yn", BAD_REQ);
    request.resetParseStat();

    APEND_BUF(buf, request, "set yn a \r\n yn", BAD_REQ);
    request.resetParseStat();
    APEND_BUF(buf, request, "set yn 32 a\r\n yn", BAD_REQ);
    request.resetParseStat();
    APEND_BUF(buf, request, "set yn 32 32 a\r\n yn", BAD_REQ);
    request.resetParseStat();
}

TEST_F(ReqTest, test_req_type)
{
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

TEST_F(ReqTest, req_get)
{
    TEST_GET(buf, "get \r\n", BAD_REQ, 0);
    TEST_GET(buf, "get", NOT_ALL, 0);
    TEST_GET(buf, "g\r\n", PARSE_UNKNOWN_REQ, 0);

    TEST_GET(buf, "get yn\r\n", PARSE_OK, 1);
    TEST_GET(buf, "get yn yn1\r\n", PARSE_OK, 2);
    TEST_GET(buf, "get yn yn1 yn2\r\n", PARSE_OK, 3);
    TEST_GET(buf, "get yn \r\n", PARSE_OK, 1);
    TEST_GET(buf, "get yn yn1 \r\n", PARSE_OK, 2);
}


TEST_F(ReqTest, req_delete)
{
    request.resetParseStat();
    TEST_PARSE(buf, request, "delete \r\n", BAD_REQ);
    TEST_PARSE(buf, request, "delete yn\r\n", PARSE_OK);
    request.resetParseStat();
    TEST_PARSE(buf, request, "delete", NOT_ALL);
    TEST_PARSE(buf, request, "key\r\n", PARSE_OK);
}

