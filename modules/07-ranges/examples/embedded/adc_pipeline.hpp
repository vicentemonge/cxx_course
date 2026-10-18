#pragma once
#include <algorithm>
#include <cstdint>
#include <ranges>
#include <span>

namespace m07 {

// Convierte cuentas ADC de 12 bits a mV y cuenta muestras por encima de un umbral,
// descartando valores saturados.
inline auto above_threshold(std::span<const std::uint16_t> samples, std::int32_t threshold_mv) {
    auto to_mv = [](std::uint16_t c) { return static_cast<std::int32_t>(c) * 3300 / 4095; };
    auto valid = [](std::uint16_t c) { return c < 4095; };
    return std::ranges::count_if(samples | std::views::filter(valid) | std::views::transform(to_mv),
                                 [threshold_mv](std::int32_t mv) { return mv > threshold_mv; });
}

} // namespace m07
