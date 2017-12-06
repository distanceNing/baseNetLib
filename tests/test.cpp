#include "test.h"
#include "../net/socket/socket_buf.h"
#include "../mem_request.h"
#include "../data_structer.h"
#include "../mem_response.h"
#include "test_common.h"
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;


//#define TEST_RESPONSE(expect,a)
#define TEST_REQ_TYPE(request,buf,str,result) \
do{\
	buf.resetBuffer();\
	buf.append(str);\
	request.parse(buf);\
	EXPECT_EQ_INT(result,request.getRequestType());\
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

void testParseType()
{
	Request request;
	net::SocketBuf buf;
	TEST_REQ_TYPE(request,buf,"set yn 32 1023434 8\r\n yn\r\n",REQ_SET);
	request.resetParseStat();
	TEST_REQ_TYPE(request,buf,"get yn\r\n",REQ_GET);
	request.resetParseStat();
	TEST_REQ_TYPE(request,buf,"delete\r\n",REQ_FAIL);
	request.resetParseStat();
	TEST_REQ_TYPE(request,buf,"quit\r\n",REQ_QUIT);
	request.resetParseStat();
	TEST_REQ_TYPE(request,buf,"delete yn\r\n",REQ_DELETE);
}

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
	TEST_GET(buf,"g\r\n",PARSE_UNKNOWN_REQ,0);

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
	APEND_BUF(buf,"de\r\n",PARSE_UNKNOWN_REQ);
}
void testRequestParse()
{
	parseSet();
	parseGet();
	parseDelete();
	testParseType();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
}
void testResponse()
{

	DataStructer dataStructer;
	Response response(&dataStructer);
	response.handleDelete("yn");
	strcmp(response.getResponse(),"aa");
}

