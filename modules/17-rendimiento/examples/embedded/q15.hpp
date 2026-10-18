#pragma once
// Punto fijo Q15 con saturación: aritmética fraccionaria en MCUs sin FPU · @performance @emb:ok
#include <algorithm>
#include <cstdint>
#include <limits>

namespace m17 {

class Q15 {
public:
    constexpr Q15() = default;
    static constexpr Q15 desde_raw(std::int16_t r) { Q15 q; q.v_ = r; return q; }
    static constexpr Q15 desde_float(float f) {
        return desde_raw(saturar(static_cast<std::int32_t>(f * 32768.0f)));
    }
    constexpr std::int16_t raw() const { return v_; }
    constexpr float a_float() const { return static_cast<float>(v_) / 32768.0f; }

    friend constexpr Q15 operator+(Q15 a, Q15 b) { return desde_raw(saturar(std::int32_t{a.v_} + b.v_)); }
    friend constexpr Q15 operator-(Q15 a, Q15 b) { return desde_raw(saturar(std::int32_t{a.v_} - b.v_)); }
    friend constexpr Q15 operator*(Q15 a, Q15 b) {
        std::int32_t p = std::int32_t{a.v_} * b.v_;           // Q30
        return desde_raw(saturar((p + (1 << 14)) >> 15));      // redondeo a Q15
    }
    friend constexpr bool operator==(Q15, Q15) = default;

private:
    static constexpr std::int16_t saturar(std::int32_t x) {
        return static_cast<std::int16_t>(std::clamp<std::int32_t>(
            x, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()));
    }
    std::int16_t v_ = 0;
};

static_assert(sizeof(Q15) == 2);
static_assert((Q15::desde_float(0.5f) * Q15::desde_float(0.5f)).raw() == Q15::desde_float(0.25f).raw());
static_assert((Q15::desde_float(0.9f) + Q15::desde_float(0.9f)).raw() == 32767);   // satura

} // namespace m17
