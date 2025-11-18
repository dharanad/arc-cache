#include <iostream>
#include "lru.h"
int main() {
    std::cout << "Hello, Arc Cache" << std::endl;
    LruCache<int, int> cache(3);
    cache.put(1,10);
    cache.put(2,15);
    cache.put(3,20);
    std::cout << cache.get(1).has_value() << std::endl;
    // std::cout << cache.get(1).value() << std::endl;

    return 0;
}