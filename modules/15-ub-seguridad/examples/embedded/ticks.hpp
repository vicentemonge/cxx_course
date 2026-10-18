#pragma once
// Comparación de ticks robusta frente a desbordamiento del contador (SysTick, timers de 32 bits).
#include <cstdint>

namespace m15 {

// Correcto: la resta sin signo es modular, el resultado es la distancia real
constexpr bool expirado(std::uint32_t ahora, std::uint32_t inicio, std::uint32_t timeout) {
    return ahora - inicio >= timeout;   // en targets con int de 16 bits haría falta un cast
}

// Incorrecto: falla cuando ahora ha dado la vuelta y inicio + timeout no
constexpr bool expirado_mal(std::uint32_t ahora, std::uint32_t inicio, std::uint32_t timeout) {
    return ahora >= inicio + timeout;
}

// inicio cerca del final del rango: inicio + timeout da la vuelta a 0x10
static_assert(!expirado(0xFFFF'FFF5u, 0xFFFF'FFF0u, 0x20u));     // 5 ticks: no expirado
static_assert(expirado_mal(0xFFFF'FFF5u, 0xFFFF'FFF0u, 0x20u));  // el bug: falso positivo
static_assert(expirado(0x0000'0010u, 0xFFFF'FFF0u, 0x20u));      // 0x20 ticks: expirado

} // namespace m15
