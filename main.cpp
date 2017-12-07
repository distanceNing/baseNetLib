#include "app.h"
#include "gtest/gtest.h"

#define _TESTING

int main(int argc, char* argv[])
{
#ifdef _TESTING
    ::testing::FLAGS_gtest_color="yes";
    ::testing::InitGoogleTest(&argc, argv);
    return  RUN_ALL_TESTS();
#else

    net::EventLoop loop(net::POLL);
    App app(&loop);
    app.run();
    return 0;

#endif

}


