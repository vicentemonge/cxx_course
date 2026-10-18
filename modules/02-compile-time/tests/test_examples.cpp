#include <doctest/doctest.h>
#include "examples/embedded/crc32.hpp"

static_assert(m02::crc32("123456789") == 0xCBF43926U);

TEST_CASE("crc32 en runtime coincide con el valor de referencia") {
    std::string_view s = "123456789";
    CHECK(m02::crc32(s) == 0xCBF43926U);
}
