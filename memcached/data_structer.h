//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#ifndef MEMCACHED_DATASTRUCTER_H
#define MEMCACHED_DATASTRUCTER_H
#include "thread/lock.h"
#include "common.h"
#include "socket/socket_buf.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>
#include <sstream>

struct ValueInfo {
  uint32_t flags_;
  int32_t exptime_;
  uint64_t cas_;
  uint32_t value_len_;
  char* value_;
  ValueInfo()
          :value_(NULL), flags_(0), exptime_(0), cas_(0), value_len_(0)
  {
  }
  void setValue(const char* value, uint32_t len)
  {
      if ( value_ != NULL )
          delete[]value_;
      value_ = new char[len];
      memcpy(value_, value, len);
  }

  void setValue(net::SocketBuf& sock_buf)
  {
      if ( value_ != NULL )
          delete[]value_;
      value_ = new char[value_len_ + 2];
      sock_buf.read(value_, value_len_ + 2);
      value_len_ += 2;
  }

  const ValueInfo& operator=(ValueInfo& rv);

  void printInfo() const
  {
      std::cout << "value_len_ : " << value_len_ << "\nvalue_     : " << value_ << "\nflags_     : " << flags_
                << "\nexptime_   : " << exptime_ << "\ncas_       : " << cas_ << std::endl;
  }

  const std::string packInfo(const std::string& key) const
  {
      /*
       *  VALUE <key> <flags> <bytes> [<cas unqiue>]\r\n
       *  <data block>\r\n
       *   END\r\n
       */
      std::ostringstream oss;
      oss << "VALUE " << key << " " << flags_ << " " << value_len_ << "\r\n" << value_ << "\r\nEND\r\n";
      return oss.str();
  }
};

typedef struct {
  MutexLock nodeLock_;
  std::unordered_map<std::string, std::unique_ptr<ValueInfo, std::function<void(ValueInfo*)>>> nodeMap_;
} Node;

class DataStructer {
public:
    enum OperatorRes {
      kOperatorOk = 100, kExisted, kOperatorFail, kNotFound,
    };
    static const size_t kInitBucketSize = 8;

    DataStructer()
            :dataStructer_(kInitBucketSize)
    {
    }

    OperatorRes insert(const std::string& key, ValueInfo* value_info);

    const ValueInfo* getValue(const std::string& key) const;

    OperatorRes remove(const std::string& key);

    OperatorRes append(const std::string& key, const char* data, const size_t data_len);

    size_t elementSize() const
    {
        size_t count = 0;
        for (auto& ite : dataStructer_) {
            count += ite.nodeMap_.size();
        }
        return count;
    }

    ~DataStructer()
    {
    }
private:

    inline Node& find(const char* key)
    {
        size_t index = hashFun(key) % dataStructer_.size();
        return dataStructer_.at(index);
    }
    inline Node& find(const std::string& key)
    {
        size_t index = hashFun(key) % dataStructer_.size();
        return dataStructer_.at(index);
    }
    inline size_t hashFun(const char* key) const
    {
        size_t hash_code = std::hash<std::string>()(std::string(key));
        return hash_code;
    }

    inline size_t hashFun(const std::string key) const
    {
        size_t hash_code = std::hash<std::string>()(key);
        return hash_code;
    }

private:

    std::vector<Node> dataStructer_;
};

#endif //MEMCACHED_DATASTRUCTER_H
