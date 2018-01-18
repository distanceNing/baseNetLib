//#include "MemServer.h"
//#include "gtest/gtest.h"
//#define _TESTING
#include "mem_pool.h"
#include <chrono>
#include <iostream>

class Rational {
public:

    /*static MemPool memPool;

    inline void* operator new(size_t size)
    {
        return memPool.alloc(size);
    }

    inline void operator delete(void* block, size_t size)
    {
        memPool.free(block, size);
    }
*/

    static MemoryPool<Rational> memoryPool;

    inline void* operator new(size_t size)
    {
        return memoryPool.alloc(size);
    }

    inline void operator delete(void* block, size_t size)
    {
        memoryPool.free(block, size);
    }

    Rational(int x = 0, int y = 1) :n(x), d(y) {}

private:
    int n;
    int d;
};
//MemPool Rational::memPool;
MemoryPool<Rational> Rational::memoryPool;
int main(int argc, char* argv[])
{

#ifdef _TESTING
    ::testing::FLAGS_gtest_color="yes";
    ::testing::InitGoogleTest(&argc, argv);
    return  RUN_ALL_TESTS();
#else

	//std::chrono::seconds start(60);
	auto t1 = std::chrono::system_clock::now();
	Rational *ra[1000];


	for (int j = 0;j < 50000;++j)
	{
		for (int i = 0;i < 1000;++i)
		{
			ra[i] = new Rational;
		}
		for (int i = 0;i < 1000;++i)
		{
			delete ra[i];
		}
	}

	auto t2 = std::chrono::system_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds >(t2 - t1).count() <<" ms" <<std:: endl;
	/*
	 *  globe new and delete spend time is 1328 ms
	 *  version 1 : 380 ms
	 *  version 2:  620 ms
	 *  version 3:  1160 ms
	 *
	 *
	 */




    //net::EventLoop loop(net::POLL);
    //MemServer memServer(&loop);
    //memServer.run();
    return 0;
#endif

}


