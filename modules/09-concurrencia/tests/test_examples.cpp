#include <doctest/doctest.h>
#include "examples/spsc_ring.hpp"
#include <thread>

TEST_CASE("SpscRing conserva orden entre hilos") {
    m09::SpscRing<int, 16> q;
    constexpr int kN = 10000;
    std::jthread producer{[&] { for (int i = 0; i < kN; ++i) while (!q.push(i)) std::this_thread::yield(); }};
    int expected = 0;
    while (expected < kN) {
        if (auto v = q.pop()) { REQUIRE(*v == expected); ++expected; } else { std::this_thread::yield(); }
    }
}
