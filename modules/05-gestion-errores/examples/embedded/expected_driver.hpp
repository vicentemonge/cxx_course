#pragma once
#include <cstdint>
#include <expected>

namespace m05 {

enum class DriverError : std::uint8_t { NotInitialized, Timeout, BadConfig };

class Sensor {
public:
    [[nodiscard]] std::expected<void, DriverError> init() { ready_ = true; return {}; }

    [[nodiscard]] std::expected<void, DriverError> configure(std::uint32_t rate_hz) {
        if (!ready_) return std::unexpected(DriverError::NotInitialized);
        if (rate_hz == 0 || rate_hz > 1000) return std::unexpected(DriverError::BadConfig);
        rate_ = rate_hz;
        return {};
    }

    [[nodiscard]] std::expected<std::int32_t, DriverError> read() const {
        if (rate_ == 0) return std::unexpected(DriverError::NotInitialized);
        return 42;
    }

private:
    bool ready_ = false;
    std::uint32_t rate_ = 0;
};

inline std::expected<std::int32_t, DriverError> bring_up(Sensor& s, std::uint32_t rate) {
    return s.init()
        .and_then([&] { return s.configure(rate); })
        .and_then([&] { return s.read(); });
}

} // namespace m05
