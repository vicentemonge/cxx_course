#include <doctest/doctest.h>
#include "examples/register_concept.hpp"

static_assert(m03::mask(0U, 2U) == 0b101U);
static_assert(!m03::RegisterAccess<int>);

TEST_CASE("GpioDriver sobre banco simulado") {
    course::hal::FakeRegisterBank<16> bank;
    m03::GpioDriver gpio{bank};
    gpio.set(3);
    CHECK(gpio.get(3));
    gpio.clear(3);
    CHECK_FALSE(gpio.get(3));
}
