#include "cache.h"
#include <list>
#include <unordered_map>
#include <functional>

template <typename KeyType, typename ValueType>
class LruCache : public Cache<KeyType, ValueType>
{
public:
    LruCache(size_t capacity);
    LruCache(size_t capacity, std::function<void(KeyType, ValueType)> evictionHandler);
    void put(KeyType key, ValueType value) override;
    std::optional<ValueType> get(KeyType key) override;
    std::size_t size() override;
    std::size_t capacity() override;

private:
    using ListNodePtr = typename std::list<std::pair<KeyType, ValueType>>::iterator;

    /// @brief New elements are insert at back
    std::list<std::pair<KeyType, ValueType>> recentlyUsedList_;
    std::unordered_map<KeyType, ListNodePtr> map_;
    size_t capacity_;
    size_t size_;
    std::function<void(KeyType, ValueType)> evictionHandler_;

    // Helper fuctions
    /// @brief Access the element, remove it form current pos and put it infront of the list
    void touch(ListNodePtr ptr);
    void insert(KeyType key, ValueType value);
    void evict();
};