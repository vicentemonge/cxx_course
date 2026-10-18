#include <doctest/doctest.h>
#include "examples/register_field.hpp"

TEST_CASE("Field inserta sin tocar otros bits") {
    using F = m13::Field<4, 4>;
    constexpr std::uint32_t r = F::insert(0xFFFF'FFFFU, 0x5);
    static_assert(r == 0xFFFF'FF5FU);
    CHECK(F::extract(r) == 0x5);
    CHECK(F::insert(0, 0xFF) == 0xF0);  // el valor se recorta al ancho
}
