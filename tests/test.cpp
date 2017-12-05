#include "test.h"
#include "../net/socket/socket_buf.h"
#include "../mem_request.h"
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) \
			EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

#define EXPECT_EQ_STRING(expect,parse_str) \
	do{\
		EXPECT_EQ_INT(0, strcmp(expect, parse_str,len));\
	}while(0)

#define APEND_BUF(buf,str,result) \
do{\
	buf.resetBuffer();\
	buf.append(str);\
	Request request;\
	EXPECT_EQ_INT(result,request.parse(buf));\
}while(0)


#define TEST_GET(buf,str,result,key_num) \
do{\
	buf.resetBuffer();\
	buf.append(str);\
	Request request;\
	EXPECT_EQ_INT(result,request.parse(buf));\
	EXPECT_EQ_INT(key_num,request.getKeyCount());\
}while(0)

void parseSet()
{
	net::SocketBuf buf;
	APEND_BUF(buf,"set yn 32 1023434 8\r\n",NEED_DATA_BLOCK);
	APEND_BUF(buf,"set yn 32 102343",NOT_ALL);
	APEND_BUF(buf,"set yn 32 1023434 8\r\n yn\r\n",PARSE_OK);
	APEND_BUF(buf,"set yn 32 1023434 8\r\n yn",NEED_DATA_BLOCK);

	APEND_BUF(buf,"set   \r\n yn",BAD_REQ);
	APEND_BUF(buf,"set yn  \r\n yn",BAD_REQ);
	APEND_BUF(buf,"set yn 32 \r\n yn",BAD_REQ);
	APEND_BUF(buf,"set yn 32 1023434  \r\n yn",BAD_REQ);


	APEND_BUF(buf,"set yn a \r\n yn",BAD_REQ);
	APEND_BUF(buf,"set yn 32 a\r\n yn",BAD_REQ);
	APEND_BUF(buf,"set yn 32 32 a\r\n yn",BAD_REQ);
}
void parseGet()
{
	net::SocketBuf buf;
	TEST_GET(buf,"get \r\n",BAD_REQ,0);
	TEST_GET(buf,"get",NOT_ALL,0);
	TEST_GET(buf,"g\r\n",UNKNOWN_REQ,0);

	TEST_GET(buf,"get yn\r\n",PARSE_OK,1);
	TEST_GET(buf,"get yn yn1\r\n",PARSE_OK,2);
	TEST_GET(buf,"get yn yn1 yn2\r\n",PARSE_OK,3);
	TEST_GET(buf,"get yn \r\n",PARSE_OK,1);
	TEST_GET(buf,"get yn yn1 \r\n",PARSE_OK,2);
}
void parseDelete()
{
	net::SocketBuf buf;
	APEND_BUF(buf,"delete \r\n",BAD_REQ);
	APEND_BUF(buf,"delete yn\r\n",PARSE_OK);
	APEND_BUF(buf,"delete",NOT_ALL);
	APEND_BUF(buf,"de\r\n",UNKNOWN_REQ);
}
void testRequestParse()
{
	parseSet();
	parseGet();
	parseDelete();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
}

