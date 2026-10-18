#include <doctest/doctest.h>
#include "examples/embedded/static_logger.hpp"
#include <string>

TEST_CASE("StaticLogger formatea y trunca sin heap") {
    m11::StaticLogger<64> log;
    CHECK(log.log("{}", m11::Telemetry{235, 3700}) == "T=23.5C Vbat=3700mV");

    m11::StaticLogger<4> small;
    CHECK(small.log("{}", 123456) == "1234");
}
