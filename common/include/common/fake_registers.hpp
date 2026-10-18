#pragma once
// Banco de registros simulado para ejecutar en host los ejercicios de drivers.
// En el target real se sustituye por direcciones MMIO.

#include <array>
#include <cstddef>
#include <cstdint>

namespace course::hal {

template <std::size_t N>
class FakeRegisterBank {
public:
    [[nodiscard]] std::uint32_t read(std::size_t offset) const { return regs_.at(offset / 4); }
    void write(std::size_t offset, std::uint32_t value) { regs_.at(offset / 4) = value; }

    void set_bits(std::size_t offset, std::uint32_t mask) { write(offset, read(offset) | mask); }
    void clear_bits(std::size_t offset, std::uint32_t mask) { write(offset, read(offset) & ~mask); }

private:
    std::array<std::uint32_t, N> regs_{};
};

} // namespace course::hal
