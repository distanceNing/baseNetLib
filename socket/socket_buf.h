//
// Created by yangning on 17-11-7.
//
// Descriprion :user socket buffer 
//
// Copyright (c) yangning All rights reserved.
//

#ifndef BASE_NET_LIB_SOCKETBUF_H
#define BASE_NET_LIB_SOCKETBUF_H

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <cstring>
#include <unistd.h>
#include <sys/uio.h>
namespace net {

class SocketBuf {
public:
    static const size_t kInitSize = 1024;
    static const size_t kPrepend = 8;
    SocketBuf(size_t init_size = kInitSize, size_t prepend = kPrepend)
            :readIndex_(prepend), writeIndex_(prepend), capacity_(prepend + init_size)
    {
        buffer_ = new char[capacity_];
        memset(buffer_, 0, capacity_);
    }
    //write

    ssize_t readFromFd(int fd);

    void append(const std::string str)
    {
        write(str.c_str(), str.size());
    }

    void append(const char* str,size_t len)
    {
        write(str,len);
    }

    void write(const char* txt, size_t len);

    bool write(net::SocketBuf& buf, size_t bytes);

    void writeSkip(size_t len)
    {
        writeIndex_ += len;
    }
    //read
    void skip(size_t len)
    {
        readIndex_ += len;
    }

    bool read(char* txt, size_t bytes);

    bool read(net::SocketBuf& buf, size_t bytes);

    std::string read(size_t len)
    {
        assert(readableBytes() > len);
        return std::string(readBegin(), len);
    }

    char readByte()
    {
        char c = *readBegin();
        skip(1);
        return c;
    }

    int32_t readInt32()
    {
        int32_t ret = 0;
        memcpy(&ret, readBegin(), sizeof(int32_t));
        skip(sizeof(int32_t));
        return ret;
    }

    ~SocketBuf()
    {
        delete[] buffer_;
        buffer_ = nullptr;
        capacity_ = 0;
    }
public:

    char* readBegin()
    {
        return begin() + readIndex_;
    }

    const char* readBegin() const
    {
        return begin() + readIndex_;
    }

    char* writeBegin()
    {
        return begin() + writeIndex_;
    }

    const char* writeBegin() const
    {
        return begin() + writeIndex_;
    }

    size_t readableBytes() const
    {
        assert(writeIndex_ - readIndex_ >= 0);
        return writeIndex_ - readIndex_;
    }

    size_t writeableBytes() const
    {
        assert(capacity_ - writeIndex_ >= 0);
        return capacity_ - writeIndex_;
    }

    size_t prependBytes() const
    {
        assert(readIndex_ >= kPrepend);
        return readIndex_ - kPrepend;
    }
    //find
public:
    const char* kCRLF = "\r\n";

    char* findCRLF()
    {
        char* ptr = std::search(readBegin(), writeBegin(), kCRLF, kCRLF + 2);
        return ptr == writeBegin() ? NULL : ptr;
    }

    const char* findCRLF()const
    {
        const char* ptr = std::search(readBegin(), writeBegin(), kCRLF, kCRLF + 2);
        return ptr == writeBegin() ? NULL : ptr;
    }

    const char* findCRLF(const char* start)
    {
        const char* ptr = std::search(start, static_cast<const char*> (writeBegin()), kCRLF, kCRLF + 2);
        return ptr == writeBegin() ? NULL : ptr;
    }
private:
    static const float kGrowthFactor;

    void grow(size_t len);

    const char* begin() const
    {
        return buffer_;
    }

    char* begin()
    {
        return buffer_;
    }
    char* buffer_;
    size_t capacity_;
    size_t readIndex_;
    size_t writeIndex_;

};

} //namespace net

#endif //BASE_NET_LIB_SOCKETBUF_H
