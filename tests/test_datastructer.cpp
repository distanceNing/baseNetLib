#include "gtest/gtest.h"
#include "../data_structer.h"
class TestDataStructer : public ::testing::TestWithParam<std::string> {
protected:
    //第一个case执行前执行
    static void SetUpTestCase()
    {
        //std::cout << "before test case\n";

    }
    //SetUp()方法在每个TestCase之前执行
    virtual void SetUp()
    {
        ValueInfo valueInfo;
        valueInfo.cas_ = 0;
        valueInfo.flags_ = 0;
        valueInfo.exptime_ = 0;
        valueInfo.value_len_ = 5;
        valueInfo.setValue("yn001", valueInfo.value_len_);

        dataStructer_.insert("yn", &valueInfo);
        //std::cout<<"insert a value "<<std::endl;
    }
    // TearDown()方法在每个TestCase之后执行
    virtual void TearDown()
    {
        dataStructer_.remove("yn");
        //std::cout<<"remove a init value "<<std::endl;
    }
    static void TearDownTestCase()
    {
       // std::cout << "after test case\n";
    }
    DataStructer dataStructer_;
    ValueInfo* valueInfo_;
};

#define TEST_STRING_EQ(str1,str2,len) do{\
    EXPECT_EQ(0,strncmp(str1,str2,len));\
}while(0)

TEST_F(TestDataStructer,TestInsert)
{
    EXPECT_EQ(1,dataStructer_.elementSize());
    ValueInfo valueInfo;
    valueInfo.cas_ = 0;
    valueInfo.flags_ = 0;
    valueInfo.exptime_ = 0;
    valueInfo.value_len_ = 5;
    valueInfo.setValue("yn001", valueInfo.value_len_);

    EXPECT_EQ(DataStructer::kExisted,dataStructer_.insert("yn", &valueInfo));
    EXPECT_EQ((int)DataStructer::kOperatorOk,dataStructer_.insert("yn1", &valueInfo));
    EXPECT_EQ(2,dataStructer_.elementSize());
    TEST_STRING_EQ("yn001",dataStructer_.getValue("yn")->value_,5);
    EXPECT_EQ(5,dataStructer_.getValue("yn")->value_len_);
    EXPECT_EQ(nullptr,dataStructer_.getValue("aa"))<<"aa not found";

}

TEST_F(TestDataStructer,TestAppend)
{

    EXPECT_EQ((int)DataStructer::kOperatorOk,dataStructer_.append("yn", "hello world", 11));
    TEST_STRING_EQ("yn001hello world",dataStructer_.getValue("yn")->value_,11+5);
    EXPECT_EQ(11+5,dataStructer_.getValue("yn")->value_len_);
}


TEST_F(TestDataStructer,TestRemove)
{

    EXPECT_EQ((int)DataStructer::kOperatorOk,(int)dataStructer_.remove("yn"));
    EXPECT_EQ(nullptr,dataStructer_.getValue("yn"));
    EXPECT_EQ((int)DataStructer::kNotFound,(int)dataStructer_.remove("AA"));

}


