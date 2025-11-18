#include "cache.h"
#include <vector>
#include <map>
#include <functional>

template <typename KeyType, typename ValueType>
class LruCache : public Cache<KeyType, ValueType>
{
public:
    LruCache(size_t capacity);
    LruCache(size_t capacity, std::function<void(KeyType, ValueType)> evictionHandler = nullptr);
    void put(KeyType key, ValueType value) override;
    std::optional<ValueType> get(KeyType key) override;
    std::optional<ValueType> invalidate(KeyType key) override;
    std::size_t size() override;
    std::size_t capacity() override;

private:
    std::vector<KeyType> recentlyUsedList_;
    std::map<KeyType, ValueType> map_;
    size_t capacity_;
    size_t size_;
    std::function<void(KeyType, ValueType)> evictionHandler_;
};