#include "lru.h"
#include <string>
#include <iostream>
#include <utility>

template <typename KeyType, typename ValueType>
LruCache<KeyType, ValueType>::LruCache(size_t capacity) : capacity_{capacity}, size_{0} {}

template <typename KeyType, typename ValueType>
LruCache<KeyType, ValueType>::LruCache(size_t capacity, std::function<void(KeyType, ValueType)> evictionHandler) : capacity_{capacity}, size_{0}, evictionHandler_{std::move(evictionHandler)}
{
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::put(KeyType key, ValueType value)
{
    if (this->map_.find(key) != this->map_.end())
    {
        auto ptr = this->map_[key];
        ptr->second = value;
        touch(ptr);
        return;
    }
    if (this->size_ == this->capacity_)
    {
        evict();
    }
    insert(key, value);
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> LruCache<KeyType, ValueType>::get(KeyType key)
{
    if (this->map_.find(key) == this->map_.end())
        return std::nullopt;
    ListNodePtr ptr = this->map_[key];
    touch(ptr);
    return this->recentlyUsedList_.back().second;
}

template <typename KeyType, typename ValueType>
std::size_t LruCache<KeyType, ValueType>::size()
{
    return size_;
}

template <typename KeyType, typename ValueType>
std::size_t LruCache<KeyType, ValueType>::capacity()
{
    return capacity_;
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::touch(ListNodePtr ptr)
{
    std::pair<KeyType, ValueType> element = *ptr;
    this->recentlyUsedList_.erase(ptr);
    this->recentlyUsedList_.push_back(element);
    this->map_[element.first] = std::prev(this->recentlyUsedList_.end());
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::insert(KeyType key, ValueType value)
{
    auto element = std::make_pair(key, value);
    this->recentlyUsedList_.push_back(element);
    this->map_[element.first] = std::prev(this->recentlyUsedList_.end());
    ++this->size_;
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::evict()
{
    auto victim = this->recentlyUsedList_.front();
    this->map_.erase(victim.first);
    this->recentlyUsedList_.pop_front();
    if(this->evictionHandler_) {
        this->evictionHandler_(victim.first, victim.second);
    }
    --this->size_;
}

template class LruCache<int, int>;
template class LruCache<std::string, int>;
template class LruCache<std::string, std::string>;