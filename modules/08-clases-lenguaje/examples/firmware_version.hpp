#pragma once
#include <compare>
#include <cstdint>

namespace m08 {

struct FirmwareVersion {
    std::uint8_t major = 0;
    std::uint8_t minor = 0;
    std::uint16_t patch = 0;
    auto operator<=>(const FirmwareVersion&) const = default;
};

enum class Mode : std::uint8_t { Master, Slave };

struct SpiConfig {
    Mode mode = Mode::Master;
    std::uint32_t clock_hz = 1'000'000;
    std::uint8_t cpol = 0;
    std::uint8_t cpha = 0;
};

} // namespace m08
