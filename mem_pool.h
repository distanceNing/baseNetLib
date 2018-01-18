
#ifndef MEMCACHED_MEMPOOL_H
#define MEMCACHED_MEMPOOL_H
#include <cstdlib>
#include <iostream>
class MemoryBlock {
public:
	MemoryBlock* next;
};

template<class T>
class MemoryPool {
public:
	static const  size_t kInitMemPoolSize = 32;
	MemoryPool()
	{
	}

	void expendMemPool()
	{
		size_t size = sizeof(T) > sizeof(MemoryBlock*) ? sizeof(T) : sizeof(MemoryBlock*);
		MemoryBlock* space = static_cast<MemoryBlock*>(malloc(size));
		memPool = space;

		for (int i = 0;i < kInitMemPoolSize;++i)
		{
			space->next = static_cast<MemoryBlock*>(malloc(size));
			space = space->next;
		}
		space = nullptr;
	}

	void* alloc(size_t size)
	{
		if (memPool == nullptr)
			expendMemPool();
		MemoryBlock* temp = memPool;
		memPool = memPool->next;
		return static_cast<void*>(temp);
	}

	void free(void* block, size_t size)
	{
		MemoryBlock* head = static_cast<MemoryBlock*>(block);
		head->next = memPool;
		memPool = head;
	}


	void deleteMemPool()
	{
		std::cout << "delete mempool\n";
		if (memPool == nullptr)
			return;
		MemoryBlock* temp;
		while (memPool != nullptr)
		{
			temp = memPool;
			memPool = memPool->next;
			::free(temp);
		}
	}

	~MemoryPool()
	{
		deleteMemPool();
	}

private:
	MemoryBlock* memPool;
};
#endif//!MEMCACHED_MEMPOOL_H