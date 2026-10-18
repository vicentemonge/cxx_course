// Inyección de dependencias con concepts: código testable sin virtual · @tooling @generic
#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>

template <typename C>
concept Reloj = requires(C c) { { c.ahora_ms() } -> std::convertible_to<std::uint64_t>; };

struct RelojSistema {
    std::uint64_t ahora_ms() const {
        using namespace std::chrono;
        return static_cast<std::uint64_t>(
            duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
    }
};

struct RelojFalso {
    std::uint64_t t = 0;
    std::uint64_t ahora_ms() const { return t; }
};

// Lógica bajo prueba: limitador de frecuencia (máximo un evento por periodo)
template <Reloj R>
class Limitador {
public:
    Limitador(const R& reloj, std::uint64_t periodo_ms) : reloj_{reloj}, periodo_{periodo_ms} {}
    bool permitir() {
        auto t = reloj_.ahora_ms();
        if (primero_ || t - ultimo_ >= periodo_) {
            ultimo_ = t;
            primero_ = false;
            return true;
        }
        return false;
    }

private:
    const R& reloj_;
    std::uint64_t periodo_;
    std::uint64_t ultimo_ = 0;
    bool primero_ = true;
};

int main() {
    // En el test, el tiempo es determinista
    RelojFalso reloj;
    Limitador lim{reloj, 100};
    assert(lim.permitir());
    reloj.t = 50;
    assert(!lim.permitir());
    reloj.t = 100;
    assert(lim.permitir());

    // En producción, el mismo código con el reloj real
    RelojSistema real;
    Limitador prod{real, 1000};
    assert(prod.permitir());
}
