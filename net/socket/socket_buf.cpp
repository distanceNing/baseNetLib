//
// Created by yangning on 17-11-7.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "socket_buf.h"
#include "../common.h"
#include <assert.h>

namespace net {

const float SocketBuf::kGrowthFactor = 1.5;
bool net::SocketBuf::read(char* data, size_t bytes)
{
    assert(data != NULL && bytes >= 0);
    if (bytes > readableBytes())
        return false;
    const char* temp=readBegin();
    memcpy(data, temp, bytes);
    skip(bytes);
    return true;
}

bool net::SocketBuf::read(net::SocketBuf& buf, size_t bytes)
{
    assert(bytes >= 0);
    if (bytes > readableBytes())
        return false;
    read(buf.writeBegin(), bytes);
    buf.writeIndex_ += bytes;
    return true;
}

void net::SocketBuf::write(const char* data, size_t len)
{
    assert(data != NULL && len > 0);
    if (len > writeableBytes()) {
        grow(len);
    }
    memcpy(buffer_ + writeIndex_, data, len);
    writeIndex_ += len;
}

bool net::SocketBuf::write(net::SocketBuf& buf, size_t bytes)
{
    assert(bytes > 0);
    if (bytes > writeableBytes())
        return false;
    write(buf.readBegin(), bytes);
    buf.readIndex_ += bytes;
    return true;
}

void SocketBuf::grow(size_t len)
{
    if (writeableBytes() + prependBytes() < len + kPrepend) {
        size_t size = static_cast<size_t>(capacity_ * kGrowthFactor + len);
        char* buf = new char[size];
        memset(buf, 0, size);
        assert(buf != NULL);
        memcpy(buf, buffer_, capacity_);
        delete[] buffer_;
        buffer_ = buf;
        capacity_ = size;
    }
    else {
        size_t readable = readableBytes();
        memmove(begin() + kPrepend, readBegin(), readable);
        readIndex_ = kPrepend;
        writeIndex_ = readIndex_ + readable;
    }
}
ssize_t SocketBuf::readFromFd(int fd)
{
    char extrabuf[65535] = {'\0'};
    size_t writeable = writeableBytes();
    struct iovec iov[2];
    iov[0].iov_base = writeBegin();
    iov[0].iov_len = writeable;
    iov[1].iov_base = extrabuf;
    iov[1].iov_len = 65535;

    ssize_t read_size = readv(fd, iov, 2);
    if(read_size < 0)
        //
    {
        if(errno == ECONNRESET)
            return 0;
        else
            printErrorMsg("readv");
    }
    if (read_size > writeable) {
        writeIndex_ += writeable;
        write(extrabuf, read_size - writeable);
    }
    else
        writeIndex_ += read_size;
    return read_size;
}

}//namespace net