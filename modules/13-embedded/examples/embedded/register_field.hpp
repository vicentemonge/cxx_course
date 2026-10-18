#pragma once
#include <bit>
#include <cstdint>

namespace m13 {

// Campo de bits [Offset, Offset+Width) dentro de un registro de 32 bits.
template <unsigned Offset, unsigned Width>
struct Field {
    static_assert(Width > 0 && Offset + Width <= 32);
    static constexpr std::uint32_t mask =
        (Width == 32 ? 0xFFFFFFFFU : ((1U << Width) - 1U)) << Offset;

    static constexpr std::uint32_t insert(std::uint32_t reg, std::uint32_t value) {
        return (reg & ~mask) | ((value << Offset) & mask);
    }
    static constexpr std::uint32_t extract(std::uint32_t reg) { return (reg & mask) >> Offset; }
};

// Ejemplo: USART_CR1 (STM32F4)
using UE = Field<13, 1>;
using M = Field<12, 1>;
using PCE = Field<10, 1>;

static_assert(UE::mask == 0x2000U);
static_assert(std::popcount(Field<4, 3>::mask) == 3);
static_assert(std::countr_zero(Field<4, 3>::mask) == 4);

} // namespace m13
