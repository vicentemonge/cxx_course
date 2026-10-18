// Overflow: con signo es UB, sin signo es aritmética modular · @safety
#include <cassert>
#include <climits>
#include <cstdint>
#include <limits>
#include <optional>

// El compilador puede asumir que x + 1 > x para int y eliminar esta comprobación
bool ingenuo(int x) { return x + 1 > x; }   // siempre "true" tras optimizar

// Comprobación correcta: antes de operar
std::optional<int> suma_segura(int a, int b) {
    if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
        (b < 0 && a < std::numeric_limits<int>::min() - b)) {
        return std::nullopt;
    }
    return a + b;
}

// Una evaluación constante con UB no compila: los static_assert detectan UB
constexpr int doble(int x) { return x * 2; }
static_assert(doble(1000) == 2000);
// static_assert(doble(INT_MAX) > 0);   // error: overflow en expresión constante

int main() {
    assert(ingenuo(5));
    assert(!suma_segura(INT_MAX, 1));
    assert(suma_segura(2, 3) == 5);

    std::uint8_t u = 255;
    u = static_cast<std::uint8_t>(u + 1);   // definido: 0
    assert(u == 0);

    // Desplazar 32 bits un valor de 32 bits también es UB
    std::uint32_t one = 1;
    unsigned n = 31;
    assert((one << n) == 0x8000'0000u);
    // (one << 32) -> UB

#if defined(__cpp_lib_saturation_arithmetic)
    assert(std::add_sat<std::uint8_t>(250, 10) == 255);   // [26]
#endif
}
