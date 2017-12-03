//
// Created by yangning on 17-12-3.
//
// Descriprion :
//
// Copyright (c) yangning All rights reserved.
//

#include "data_structer.h"
#include "common.h"
#include <hash_fun.h>
#include <cstring>
bool DataStructer::insert(const std::string& key, ValueInfo* value_info)
{
    size_t hash_code = hashFun(key);
    size_t index = hash_code % dataStructer_.size();

    Node& index_ref = dataStructer_.at(index);
    index_ref.nodeLock_.lock();
    auto result = index_ref.nodeMap_.insert(std::make_pair(key, std::unique_ptr<ValueInfo>(value_info)));
    index_ref.nodeLock_.unlock();
    return result.second;
}
const ValueInfo* DataStructer::getValue(const std::string& key) const
{
    size_t index = hashFun(key) % dataStructer_.size();
    const Node& index_ref = dataStructer_.at(index);
    auto ite = index_ref.nodeMap_.find(key);
    return ite != index_ref.nodeMap_.end() ? ite->second.get() : nullptr;
}
bool DataStructer::remove(const std::string& key)
{
    size_t index = hashFun(key) % dataStructer_.size();
    Node& index_ref = dataStructer_.at(index);
    index_ref.nodeLock_.lock();
    size_t res = index_ref.nodeMap_.erase(key);
    index_ref.nodeLock_.unlock();
    return res == 1;
}
bool DataStructer::append(const std::string& key, const char* data, const size_t data_len)
{
    Node& node_ref = find(key);
    auto ite = node_ref.nodeMap_.find(key);
    if ( ite == node_ref.nodeMap_.end())
        return false;
    char* temp = new char[data_len + ite->second->value_len_];
    assert(temp != NULL);
    memcpy(temp, ite->second->value_, ite->second->value_len_);
    memcpy(temp + ite->second->value_len_, data, data_len);
    char* ptr = ite->second->value_;
    node_ref.nodeLock_.lock();
    ite->second->value_len_ += data_len;
    ite->second->value_ = temp;
    node_ref.nodeLock_.unlock();
    delete[]ptr;
    return true;
}

