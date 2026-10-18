// Parámetros template no-tipo: auto [17], de clase y flotantes [20]
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <string_view>

template <auto V>   // [17]: el tipo se deduce del valor
constexpr auto valor = V;

// String como parámetro template [20]
template <std::size_t N>
struct FixedString {
    char buf[N]{};
    constexpr FixedString(const char (&s)[N]) { std::copy_n(s, N, buf); }
    constexpr std::string_view view() const { return {buf, N - 1}; }
};

template <FixedString Nombre>
struct Etiqueta {
    static constexpr std::string_view nombre() { return Nombre.view(); }
};

template <double Factor>   // [20]
constexpr double escalar(double x) { return x * Factor; }

int main() {
    static_assert(valor<5> == 5);
    static_assert(valor<'c'> == 'c');
    static_assert(Etiqueta<"temperatura">::nombre() == "temperatura");
    static_assert(escalar<2.5>(4.0) == 10.0);
    std::printf("%.*s\n", static_cast<int>(Etiqueta<"hola">::nombre().size()),
                Etiqueta<"hola">::nombre().data());
}
