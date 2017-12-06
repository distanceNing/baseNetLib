//
// Created by yangning on 17-12-6.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_TEST_COMMON_H
#define MEMCACHED_TEST_COMMON_H

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
		EXPECT_EQ_INT(0, strncmp(expect, parse_str,len));\
	}while(0)

#endif //MEMCACHED_TEST_COMMON_H