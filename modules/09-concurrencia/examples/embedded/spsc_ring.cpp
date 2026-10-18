#include "examples/embedded/spsc_ring.hpp"
#include <cstdio>
#include <thread>

int main() {
    m09::SpscRing<int, 64> q;
    std::jthread producer{[&] { for (int i = 0; i < 1000; ++i) while (!q.push(i)) std::this_thread::yield(); }};
    long sum = 0;
    for (int got = 0; got < 1000;) {
        if (auto v = q.pop()) { sum += *v; ++got; } else { std::this_thread::yield(); }
    }
    std::printf("sum=%ld\n", sum);
}
