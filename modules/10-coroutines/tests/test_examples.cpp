#include <doctest/doctest.h>
#include "examples/generator.hpp"
#include <vector>

TEST_CASE("fibonacci genera la secuencia esperada") {
    std::vector<unsigned> v;
    auto g = m10::fibonacci(7);
    while (g.next()) v.push_back(g.value());
    CHECK(v == std::vector<unsigned>{0, 1, 1, 2, 3, 5, 8});
}
