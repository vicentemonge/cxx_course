#include <doctest/doctest.h>
#include "lru_cache.hpp"
#include <string>
#include <thread>
#include <vector>

TEST_CASE("LRU: expulsa el menos usado recientemente") {
    LruCache<int, std::string> c{2};
    c.put(1, "uno");
    c.put(2, "dos");
    REQUIRE(c.get(1));      // 1 pasa a ser el más reciente
    c.put(3, "tres");       // expulsa 2
    CHECK(c.get(2) == nullptr);
    CHECK(*c.get(1) == "uno");
    CHECK(*c.get(3) == "tres");
    CHECK(c.size() == 2);
}

TEST_CASE("LRU: actualizar una clave existente no expulsa") {
    LruCache<std::string, int> c{2};
    c.put("a", 1);
    c.put("b", 2);
    c.put("a", 10);
    c.put("c", 3);          // expulsa b
    CHECK(*c.get("a") == 10);
    CHECK(c.get("b") == nullptr);
}

TEST_CASE("LRU concurrente: sin data races (ejecutar con TSan)") {
    LruCacheConcurrente<int, int> c{64};
    std::vector<std::jthread> hilos;
    for (int t = 0; t < 4; ++t) {
        hilos.emplace_back([&c, t] {
            for (int i = 0; i < 1000; ++i) {
                c.put(i % 100, i + t);
                (void)c.get((i * 7) % 100);
            }
        });
    }
}
