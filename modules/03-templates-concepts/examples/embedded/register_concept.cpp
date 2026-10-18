#include "examples/embedded/register_concept.hpp"
#include <cstdio>

int main() {
    course::hal::FakeRegisterBank<16> bank;
    m03::GpioDriver gpio{bank};
    gpio.set(5);
    std::printf("pin5=%d mask=0x%X\n", gpio.get(5), m03::mask(1U, 3U, 5U));
}
