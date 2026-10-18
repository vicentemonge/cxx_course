#pragma once
#include <cstdint>
#include <utility>

namespace m01 {

enum class Parity : std::uint8_t { None, Even, Odd };

struct UartConfig {
    std::uint32_t baud = 115200;
    Parity parity = Parity::None;
};

// Simula un handle de HAL en C
struct HalUart {
    int id;
    bool open;
};

class Uart {
public:
    Uart(int id, UartConfig cfg) : h_{id, true}, cfg_{cfg} {}
    ~Uart() { close(); }

    Uart(const Uart&) = delete;
    Uart& operator=(const Uart&) = delete;

    Uart(Uart&& other) noexcept
        : h_{std::exchange(other.h_, HalUart{-1, false})}, cfg_{other.cfg_} {}
    Uart& operator=(Uart&& other) noexcept {
        if (this != &other) {
            close();
            h_ = std::exchange(other.h_, HalUart{-1, false});
            cfg_ = other.cfg_;
        }
        return *this;
    }

    [[nodiscard]] bool is_open() const noexcept { return h_.open; }
    [[nodiscard]] const UartConfig& config() const noexcept { return cfg_; }

private:
    void close() noexcept { h_.open = false; }
    HalUart h_;
    UartConfig cfg_;
};

} // namespace m01
