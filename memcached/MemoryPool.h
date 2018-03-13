//
// Created by yangning on 18-1-17.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_MEMORYPOOL_H
#define MEMCACHED_MEMORYPOOL_H
#include <iostream>
#include <mutex>
#include <memory>
#include <cassert>



class MemBlock {
public:
	enum {
		kDefautBlockSize = 4096,
	};

	MemBlock(size_t block_size = MemBlock::kDefautBlockSize) :alreadyInUsing_(0),next_(nullptr)
	{
		blockSize_ = block_size > MemBlock::kDefautBlockSize ? block_size : MemBlock::kDefautBlockSize;
		data_ = new char[blockSize_];
		assert(data_ != NULL);
	}

	void* alloc(size_t size)
	{
		assert(availableSize() >= size);
		char* ret = (char*)data_ + alreadyInUsing_;
		alreadyInUsing_ += size;
		return ret;
	}

	void free(void* block,size_t size)
	{
	}

	MemBlock* & next()
	{
		return next_;
	}

	size_t availableSize()const
	{
		return blockSize_ - alreadyInUsing_;
	}

	~MemBlock()
	{
		::free(data_);
	}
	
private:
	void* data_;
	MemBlock* next_;
	size_t blockSize_;
	size_t alreadyInUsing_;
};

class MemPool {
public:
	enum {
		kInitPoolSize = 4,
	};
	MemPool(size_t block_size = MemBlock::kDefautBlockSize) :blockSize_(blockSize_) {
		memBlockList_ = new MemBlock(blockSize_);
	} 

	void* alloc(size_t size)
	{
		//std::lock_guard<std::mutex> guard(allocMutex_);
		if (memBlockList_->availableSize() < size)
		{
			expendMemPool(size);
			assert(memBlockList_ != nullptr);
		}
		return memBlockList_->alloc(size);
	}

	void free(void* block, size_t size)
	{
		//std::lock_guard<std::mutex> guard(freeMutex_);
		memBlockList_->free(block, size);
	}

	~MemPool()
	{
		MemBlock* temp;
		while (memBlockList_)
		{
			temp = memBlockList_->next();
			delete memBlockList_;
			memBlockList_ = temp;
		}
	}
private:
	void expendMemPool(size_t size)
	{
		MemBlock* space = new MemBlock(size) ;
		space->next() = memBlockList_;
		memBlockList_ = space;
	} 
private:
	std::mutex allocMutex_;
	std::mutex freeMutex_;
	MemBlock* memBlockList_;
	size_t blockSize_;
};

#endif //MEMCACHED_MEMORYPOOL_H

