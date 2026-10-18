// Tipos fuertes: hacer imposible confundir parámetros · @type-design @safety
#include <cassert>
#include <compare>
#include <cstdint>

template <typename T, typename Etiqueta>
class Fuerte {
public:
    constexpr explicit Fuerte(T v) : v_{v} {}
    constexpr T valor() const { return v_; }
    constexpr auto operator<=>(const Fuerte&) const = default;
    constexpr Fuerte operator+(Fuerte o) const { return Fuerte{v_ + o.v_}; }

private:
    T v_;
};

using Milisegundos = Fuerte<std::uint32_t, struct MilisegundosTag>;
using Hercios = Fuerte<std::uint32_t, struct HerciosTag>;

constexpr Milisegundos operator""_ms(unsigned long long v) { return Milisegundos{static_cast<std::uint32_t>(v)}; }
constexpr Hercios operator""_hz(unsigned long long v) { return Hercios{static_cast<std::uint32_t>(v)}; }

// Antes: void configurar(uint32_t periodo, uint32_t frecuencia) -> fácil invertir el orden
constexpr std::uint32_t configurar(Milisegundos periodo, Hercios frecuencia) {
    return periodo.valor() * frecuencia.valor() / 1000;
}

int main() {
    static_assert(configurar(500_ms, 2000_hz) == 1000);
    // configurar(2000_hz, 500_ms);   // error de compilación
    // Milisegundos m = 5;            // error: constructor explicit
    static_assert(100_ms + 50_ms == 150_ms);
    static_assert(sizeof(Milisegundos) == sizeof(std::uint32_t));   // coste cero
    assert(configurar(Milisegundos{1000}, Hercios{1}) == 1);
}
