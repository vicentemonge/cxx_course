// Strict aliasing: formas correctas de reinterpretar bytes [20] · @safety
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>

int main() {
    float f = 1.5f;

    // UB: acceder a un float a través de un uint32_t*
    // std::uint32_t mal = *reinterpret_cast<std::uint32_t*>(&f);

    // Correcto antes de C++20: memcpy (el compilador lo convierte en un mov)
    std::uint32_t a{};
    std::memcpy(&a, &f, sizeof a);

    // Correcto en C++20: bit_cast, además usable en constexpr
    auto b = std::bit_cast<std::uint32_t>(f);
    static_assert(std::bit_cast<std::uint32_t>(1.5f) == 0x3FC0'0000u);
    assert(a == b);

    // char, unsigned char y std::byte pueden inspeccionar cualquier objeto
    const auto* bytes = reinterpret_cast<const unsigned char*>(&f);
    unsigned suma = 0;
    for (std::size_t i = 0; i < sizeof f; ++i) suma += bytes[i];
    assert(suma > 0);
}
