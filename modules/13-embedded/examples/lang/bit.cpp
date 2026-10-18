// <bit>: manipulación de bits portable [20/23]
#include <bit>
#include <cassert>
#include <cstdint>

int main() {
    constexpr std::uint32_t x = 0b0001'0110;
    static_assert(std::popcount(x) == 3);
    static_assert(std::countr_zero(x) == 1);
    static_assert(std::countl_zero(x) == 27);
    static_assert(std::bit_width(x) == 5);
    static_assert(std::has_single_bit(64u));
    static_assert(std::bit_ceil(100u) == 128u);
    static_assert(std::bit_floor(100u) == 64u);
    static_assert(std::rotl(std::uint8_t{0b1000'0001}, 1) == 0b0000'0011);

    // bit_cast [20]: reinterpretar la representación sin UB
    constexpr float f = 1.0f;
    static_assert(std::bit_cast<std::uint32_t>(f) == 0x3F80'0000u);

#if defined(__cpp_lib_byteswap)
    static_assert(std::byteswap(std::uint32_t{0x1122'3344}) == 0x4433'2211u);   // [23]
#endif
    static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big);
    assert(std::popcount(0xFFu) == 8);
}
