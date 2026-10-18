#include <doctest/doctest.h>
#include "examples/embedded/expected_driver.hpp"

TEST_CASE("bring_up encadena con and_then") {
    m05::Sensor ok;
    CHECK(m05::bring_up(ok, 100).value() == 42);

    m05::Sensor bad;
    auto r = m05::bring_up(bad, 5000);
    REQUIRE_FALSE(r.has_value());
    CHECK(r.error() == m05::DriverError::BadConfig);
}
