#include <doctest/doctest.h>
#include "examples/embedded/q15.hpp"

TEST_CASE("Q15: multiplicación, saturación y error de redondeo") {
    using m17::Q15;
    auto a = Q15::desde_float(0.75f);
    auto b = Q15::desde_float(-0.5f);
    CHECK(static_cast<double>((a * b).a_float()) == doctest::Approx(-0.375).epsilon(1e-4));
    CHECK((Q15::desde_float(-0.9f) - Q15::desde_float(0.9f)).raw() == -32768);
    CHECK(Q15::desde_float(2.0f).raw() == 32767);
}
