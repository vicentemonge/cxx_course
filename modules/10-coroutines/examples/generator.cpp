#include "examples/generator.hpp"
#include <cstdio>

int main() {
    auto g = m10::fibonacci(10);
    while (g.next()) std::printf("%u ", g.value());
    std::printf("\n");
}
