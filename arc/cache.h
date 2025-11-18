#include <cstddef>
#include <optional>

template <typename KeyType, typename ValueType>
class Cache
{
public:
    virtual ~Cache() = default;
    /// @brief Add a key value entry into the Cache
    virtual void put(KeyType key, ValueType value) = 0;
    /// @brief Returns the value associated with the key if present
    virtual std::optional<ValueType> get(KeyType key) = 0;
    /// @brief Rmeove entry specified by the key, if present
    virtual std::optional<ValueType> invalidate(KeyType key) = 0;
    /// @brief Numnber of element that are in the cache
    virtual std::size_t size() = 0;
    /// @brief Total elements the cache can hold
    virtual std::size_t capacity() = 0;
};