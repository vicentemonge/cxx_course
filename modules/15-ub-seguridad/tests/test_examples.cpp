#include <doctest/doctest.h>
#include "examples/embedded/ticks.hpp"
#include "examples/embedded/trama_a_struct.hpp"

TEST_CASE("parsear_cabecera lee little-endian sin alineación") {
    std::array<std::byte, 9> buf{};
    const std::array raw{std::byte{0x02}, std::byte{0x10}, std::byte{0x00},
                         std::byte{0x78}, std::byte{0x56}, std::byte{0x34}, std::byte{0x12}};
    std::copy(raw.begin(), raw.end(), buf.begin() + 1);   // desalineado a propósito
    auto c = m15::parsear_cabecera(std::span{buf}.subspan(1));
    REQUIRE(c);
    CHECK(c->tipo == 2);
    CHECK(c->longitud == 0x0010);
    CHECK(c->secuencia == 0x12345678u);
    CHECK_FALSE(m15::parsear_cabecera(std::span{buf}.first(3)));
}

TEST_CASE("expirado es correcto a través del desbordamiento") {
    CHECK(m15::expirado(100, 50, 50));
    CHECK_FALSE(m15::expirado(99, 50, 50));
    CHECK(m15::expirado(0x10u, 0xFFFF'FFF0u, 0x20u));
    CHECK_FALSE(m15::expirado(0xFFFF'FFF5u, 0xFFFF'FFF0u, 0x20u));
}
