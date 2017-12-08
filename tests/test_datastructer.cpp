#include "gtest/gtest.h"
#include "data_structer.h"
class TestDataStructer : public ::testing::TestWithParam<std::string> {
protected:
    DataStructer dataStructer_;
    ValueInfo* valueInfo_;
};

#define TEST_STRING_EQ(str1,str2,len) do{\
    EXPECT_EQ(0,strncmp(str1,str2,len));\
}while(0)

TEST_F(TestDataStructer,testSet)
{
    ValueInfo* valueInfo = new ValueInfo;
    valueInfo->cas_ = 0;
    valueInfo->flags_ = 0;
    valueInfo->exptime_ = 0;
    valueInfo->value_len_ = 5;
    valueInfo->setValue("yn001", valueInfo->value_len_);

    dataStructer_.insert("yn", valueInfo);
    TEST_STRING_EQ("yn001",dataStructer_.getValue("yn")->value_,5);
    EXPECT_EQ(5,dataStructer_.getValue("yn")->value_len_);
    EXPECT_EQ(nullptr,dataStructer_.getValue("aa"))<<"aa not found";

    dataStructer_.append("yn", "hello world", 11);

    TEST_STRING_EQ("yn001hello world",dataStructer_.getValue("yn")->value_,11+5);
    EXPECT_EQ(16,dataStructer_.getValue("aa")->value_len_);

    dataStructer_.remove("yn");
    EXPECT_EQ(nullptr,dataStructer_.getValue("yn"));
}


