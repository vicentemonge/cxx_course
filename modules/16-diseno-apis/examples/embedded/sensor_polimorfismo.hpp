#pragma once
// Tres formas de polimorfismo para un driver de sensor, sin heap. Comparar tamaño en ARM.
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>

namespace m16 {

// ---- 1. Dinámico: interfaz virtual ----
struct ISensor {
    virtual std::int32_t leer() = 0;
protected:
    ~ISensor() = default;   // no se destruye a través de la interfaz: sin destructor virtual
};

// ---- 2. Estático: concept ----
template <typename T>
concept Sensor = requires(T s) { { s.leer() } -> std::same_as<std::int32_t>; };

template <Sensor S>
std::int32_t promedio(S& s, int n) {
    std::int32_t acc = 0;
    for (int i = 0; i < n; ++i) acc += s.leer();
    return acc / n;
}

// ---- 3. Type erasure con almacenamiento fijo ----
template <std::size_t Cap = 16>
class SensorRef {
public:
    template <Sensor S>
        requires(sizeof(S) <= Cap && std::is_trivially_copyable_v<S>)
    SensorRef(S s) : leer_{[](void* p) { return static_cast<S*>(p)->leer(); }} {
        ::new (static_cast<void*>(buf_.data())) S(s);
    }
    std::int32_t leer() { return leer_(buf_.data()); }

private:
    alignas(std::max_align_t) std::array<std::byte, Cap> buf_{};
    std::int32_t (*leer_)(void*);
};

// Implementaciones concretas
struct Termopar final : ISensor {
    std::int32_t valor = 250;
    std::int32_t leer() override { return valor; }
};
struct Ntc {
    std::int32_t valor = 100;
    std::int32_t leer() { return valor; }
};

} // namespace m16
