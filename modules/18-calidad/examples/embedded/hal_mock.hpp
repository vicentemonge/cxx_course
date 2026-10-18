#pragma once
// Driver testable en host: el GPIO real y el mock cumplen el mismo concept · @tooling @emb:ok
#include <concepts>
#include <cstdint>
#include <vector>

namespace m18 {

template <typename G>
concept Gpio = requires(G g, bool v) {
    { g.escribir(v) } -> std::same_as<void>;
};

// Patrón de parpadeo de error: N pulsos y pausa, avanzando un paso por tick
template <Gpio G>
class LedEstado {
public:
    explicit LedEstado(G& gpio) : gpio_{gpio} {}
    void codigo(std::uint8_t pulsos) { pulsos_ = pulsos; paso_ = 0; }
    void tick() {
        const std::uint32_t ciclo = 2u * pulsos_ + 4u;   // encendido/apagado por pulso + pausa
        if (pulsos_ == 0) { gpio_.escribir(false); return; }
        gpio_.escribir(paso_ < 2u * pulsos_ && paso_ % 2 == 0);
        paso_ = (paso_ + 1) % ciclo;
    }

private:
    G& gpio_;
    std::uint8_t pulsos_ = 0;
    std::uint32_t paso_ = 0;
};

// Mock para host: registra cada escritura
struct GpioMock {
    std::vector<bool> historial;
    void escribir(bool v) { historial.push_back(v); }
};

} // namespace m18
