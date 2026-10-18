#include <doctest/doctest.h>
#include "examples/adc_pipeline.hpp"
#include <array>

TEST_CASE("above_threshold descarta saturados") {
    constexpr std::array<std::uint16_t, 4> s{4095, 4000, 100, 3000};
    CHECK(m07::above_threshold(s, 1500) == 2);
}
