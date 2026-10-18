#pragma once
#include <array>
#include <cstdint>
#include <span>
#include <string_view>

namespace m02 {

consteval std::array<std::uint32_t, 256> make_crc32_table() {
    std::array<std::uint32_t, 256> t{};
    for (std::uint32_t i = 0; i < 256; ++i) {
        std::uint32_t c = i;
        for (int k = 0; k < 8; ++k) {
            c = (c & 1U) ? (0xEDB88320U ^ (c >> 1)) : (c >> 1);
        }
        t[i] = c;
    }
    return t;
}

inline constexpr auto crc32_table = make_crc32_table();

constexpr std::uint32_t crc32(std::string_view data) {
    std::uint32_t c = 0xFFFFFFFFU;
    for (char ch : data) {
        c = crc32_table[(c ^ static_cast<std::uint8_t>(ch)) & 0xFFU] ^ (c >> 8);
    }
    return c ^ 0xFFFFFFFFU;
}

} // namespace m02
