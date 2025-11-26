#include "arc.h"

template<typename KeyValue, typename ValueType>
Arc<KeyValue, ValueType>::Arc(std::size_t capacity) : capacity_{capacity}, size_{0} {
}

template<typename KeyType, typename ValueType>
std::size_t Arc<KeyType, ValueType>::size() {
    return size_;
}

template<typename KeyType, typename ValueType>
std::size_t Arc<KeyType, ValueType>::capacity() {
    return capacity_;
}

template<typename KeyType, typename ValueType>
void Arc<KeyType, ValueType>::put(KeyType key, ValueType value) {
}

template<typename KeyType, typename ValueType>
std::optional<ValueType> Arc<KeyType, ValueType>::get(KeyType key) {
    return std::nullopt;
}
