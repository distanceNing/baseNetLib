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
#include "net/common.h"
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

  void setValue(const char* value, uint32_t len)
  {
      value_ = new char[len];
      memcpy(value_, value, len);
  }

  void printInfo()
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
  std::unordered_map<std::string, std::unique_ptr<ValueInfo>> nodeMap_;
} Node;

class DataStructer {
public:
    static const size_t kInitBucketSize = 8;

    DataStructer()
            :dataStructer_(kInitBucketSize)
    {
    }

    bool insert(const std::string& key, ValueInfo* value_info);

    const ValueInfo* getValue(const std::string& key) const;

    bool remove(const std::string& key);

    bool append(const std::string& key, const char* data, const size_t data_len);

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
