#include "lru.h"
#include <string>

template <typename KeyType, typename ValueType>
LruCache<KeyType, ValueType>::LruCache(size_t capacity) : capacity_{capacity}, size_{0} {}

template <typename KeyType, typename ValueType>
bool LruCache<KeyType, ValueType>::put(KeyType key, ValueType value)
{
    return false;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> LruCache<KeyType, ValueType>::get(KeyType key)
{
    return std::nullopt;
}

template <typename KeyType, typename ValueType>
std::optional<ValueType> LruCache<KeyType, ValueType>::invalidate(KeyType key)
{
    return std::nullopt;
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

template class LruCache<int, int>;
// template class LruCache<std::string, int>;
// template class LruCache<std::string, std::string>;