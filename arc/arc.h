#include "cache.h"

template <typename KeyValue, typename ValueType>
class Arc : public Cache<KeyValue, ValueType>
{
public:
    Arc(std::size_t size);
    void put(KeyType key, ValueType value) override;
    std::optional<ValueType> get(KeyType key) override;
    std::size_t size() override;
    std::size_t capacity() override;
private:
    std::size_t size_;
    std::size_t capacity_;
};