#include <iostream>
#include "lru.h"
#include "test.h"

int main()
{
    std::cout << "Hello, Arc Cache" << std::endl;
    LruCache<int, int> cache(3);
    ASSERT_EQ(3, cache.capacity());
    ASSERT_EQ(0, cache.size());

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    ASSERT_EQ(3, cache.size());

    ASSERT_OPTIONAL_EQ(10, cache.get(1));
    ASSERT_OPTIONAL_EQ(20, cache.get(2));
    ASSERT_OPTIONAL_EQ(30, cache.get(3));

    ASSERT_NO_VALUE(cache.get(4));
    cache.put(4, 40);
    ASSERT_OPTIONAL_EQ(40, cache.get(4));
    ASSERT_NO_VALUE(cache.get(1));

    cache.put(2, 40);
    ASSERT_OPTIONAL_EQ(40, cache.get(2));

    cache.put(5, 50);
    ASSERT_NO_VALUE(cache.get(3));
    return 0;
}