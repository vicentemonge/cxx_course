#pragma once
// Interpretar una trama recibida por DMA/UART sin violar aliasing ni alineación.
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>
#include <span>

namespace m15 {

struct Cabecera {          // layout lógico, no el de la trama
    std::uint8_t tipo;
    std::uint16_t longitud;
    std::uint32_t secuencia;
};

// Trama en el cable (little-endian, sin padding): tipo(1) | longitud(2) | secuencia(4)
inline constexpr std::size_t kTamCabecera = 7;

template <typename T>
T leer_le(std::span<const std::byte> b) {
    std::array<std::byte, sizeof(T)> tmp{};
    std::memcpy(tmp.data(), b.data(), sizeof(T));   // sin requisitos de alineación
    T v = std::bit_cast<T>(tmp);
    if constexpr (std::endian::native == std::endian::big) {
        // byteswap [23]; aquí manual para no depender de él
        auto bytes = std::bit_cast<std::array<std::byte, sizeof(T)>>(v);
        for (std::size_t i = 0; i < sizeof(T) / 2; ++i) std::swap(bytes[i], bytes[sizeof(T) - 1 - i]);
        v = std::bit_cast<T>(bytes);
    }
    return v;
}

inline std::optional<Cabecera> parsear_cabecera(std::span<const std::byte> trama) {
    if (trama.size() < kTamCabecera) return std::nullopt;
    // Incorrecto: reinterpret_cast<const Cabecera*>(trama.data()) -> aliasing, alineación y padding
    return Cabecera{
        .tipo = std::to_integer<std::uint8_t>(trama[0]),
        .longitud = leer_le<std::uint16_t>(trama.subspan(1)),
        .secuencia = leer_le<std::uint32_t>(trama.subspan(3)),
    };
}

} // namespace m15
