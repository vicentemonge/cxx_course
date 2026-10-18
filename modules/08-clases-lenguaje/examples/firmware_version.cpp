#include "examples/firmware_version.hpp"
#include <cstdio>

int main() {
    constexpr m08::SpiConfig cfg{.clock_hz = 8'000'000, .cpha = 1};
    constexpr m08::FirmwareVersion running{1, 4, 2}, available{1, 5, 0};
    auto [maj, min, patch] = available;
    std::printf("spi=%u Hz, actualizar=%d a %u.%u.%u\n", static_cast<unsigned>(cfg.clock_hz),
                running < available, maj, min, patch);
}
