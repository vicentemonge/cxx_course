#pragma once
#include <common/fake_registers.hpp>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace m03 {

template <typename T>
concept RegisterAccess = requires(T bus, const T cbus, std::size_t off, std::uint32_t v) {
    { cbus.read(off) } -> std::same_as<std::uint32_t>;
    { bus.write(off, v) } -> std::same_as<void>;
};

static_assert(RegisterAccess<course::hal::FakeRegisterBank<16>>);

template <RegisterAccess Bus>
class GpioDriver {
public:
    static constexpr std::size_t kOdr = 0x14;
    explicit GpioDriver(Bus& bus) : bus_{bus} {}

    void set(unsigned pin) { bus_.write(kOdr, bus_.read(kOdr) | (1U << pin)); }
    void clear(unsigned pin) { bus_.write(kOdr, bus_.read(kOdr) & ~(1U << pin)); }
    [[nodiscard]] bool get(unsigned pin) const { return (bus_.read(kOdr) >> pin) & 1U; }

private:
    Bus& bus_;
};

// Fold expression: máscara a partir de una lista de pines
template <std::unsigned_integral... Pins>
constexpr std::uint32_t mask(Pins... p) { return (0U | ... | (1U << p)); }

} // namespace m03
