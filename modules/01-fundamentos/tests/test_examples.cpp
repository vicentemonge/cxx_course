#include <doctest/doctest.h>
#include "examples/raii_uart.hpp"
#include <type_traits>

static_assert(!std::is_copy_constructible_v<m01::Uart>);
static_assert(std::is_nothrow_move_constructible_v<m01::Uart>);

TEST_CASE("Uart: el movimiento transfiere la propiedad") {
    m01::Uart a{1, {}};
    m01::Uart b = std::move(a);
    CHECK_FALSE(a.is_open());
    CHECK(b.is_open());
}
