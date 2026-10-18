// static_assert como tests unitarios que se ejecutan al compilar · @tooling @compile-time
#include <array>
#include <cstddef>
#include <string_view>

constexpr bool es_palindromo(std::string_view s) {
    for (std::size_t i = 0, j = s.size(); i < j; ++i, --j) {
        if (s[i] != s[j - 1]) return false;
    }
    return true;
}

constexpr std::size_t contar_bits(unsigned v) {
    std::size_t n = 0;
    for (; v; v &= v - 1) ++n;
    return n;
}

// Tabla de casos: cada fallo es un error de compilación con el caso concreto
struct Caso { std::string_view entrada; bool esperado; };
constexpr std::array casos{Caso{"", true}, Caso{"a", true}, Caso{"abba", true},
                           Caso{"abc", false}, Caso{"reconocer", true}};

constexpr bool todos_pasan() {
    for (auto [entrada, esperado] : casos) {
        if (es_palindromo(entrada) != esperado) return false;
    }
    return true;
}

static_assert(todos_pasan());
static_assert(contar_bits(0) == 0 && contar_bits(0xFF) == 8 && contar_bits(0x8000'0001u) == 2);

int main() {}
