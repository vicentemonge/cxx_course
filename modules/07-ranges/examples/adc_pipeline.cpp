#include "examples/adc_pipeline.hpp"
#include <array>
#include <cstdio>

int main() {
    constexpr std::array<std::uint16_t, 6> s{100, 2000, 4095, 3000, 50, 2500};
    std::printf("> 1500 mV: %td\n", m07::above_threshold(s, 1500));
}
