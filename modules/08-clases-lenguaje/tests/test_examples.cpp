#include <doctest/doctest.h>
#include "examples/embedded/firmware_version.hpp"

static_assert(m08::FirmwareVersion{1, 2, 3} < m08::FirmwareVersion{1, 3, 0});
static_assert(m08::FirmwareVersion{2, 0, 0} == m08::FirmwareVersion{2, 0, 0});

TEST_CASE("designated initializers mantienen los valores por defecto") {
    constexpr m08::SpiConfig c{.cpha = 1};
    CHECK(c.clock_hz == 1'000'000);
    CHECK(c.cpha == 1);
}
