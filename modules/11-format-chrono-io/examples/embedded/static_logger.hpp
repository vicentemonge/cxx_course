#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <string_view>

namespace m11 {

struct Telemetry {
    std::int16_t temp_dc;  // décimas de °C
    std::uint16_t vbat_mv;
};

template <std::size_t N>
class StaticLogger {
public:
    template <class... Args>
    std::string_view log(std::format_string<Args...> fmt, Args&&... args) {
        auto r = std::format_to_n(buf_.data(), static_cast<std::ptrdiff_t>(N), fmt, std::forward<Args>(args)...);
        return {buf_.data(), static_cast<std::size_t>(r.out - buf_.data())};
    }

private:
    std::array<char, N> buf_{};
};

} // namespace m11

template <>
struct std::formatter<m11::Telemetry> : std::formatter<std::string_view> {
    auto format(const m11::Telemetry& t, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "T={}.{}C Vbat={}mV", t.temp_dc / 10,
                              std::abs(t.temp_dc % 10), t.vbat_mv);
    }
};
