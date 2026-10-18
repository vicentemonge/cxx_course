#pragma once
#include <array>
#include <atomic>
#include <cstddef>
#include <optional>

namespace m09 {

// Single-producer / single-consumer. N debe ser potencia de 2.
template <class T, std::size_t N>
class SpscRing {
    static_assert((N & (N - 1)) == 0, "N debe ser potencia de 2");

public:
    bool push(const T& v) {  // productor (ISR)
        const auto head = head_.load(std::memory_order_relaxed);
        if (head - tail_.load(std::memory_order_acquire) == N) return false;
        buf_[head & (N - 1)] = v;
        head_.store(head + 1, std::memory_order_release);
        return true;
    }

    std::optional<T> pop() {  // consumidor (tarea)
        const auto tail = tail_.load(std::memory_order_relaxed);
        if (tail == head_.load(std::memory_order_acquire)) return std::nullopt;
        T v = buf_[tail & (N - 1)];
        tail_.store(tail + 1, std::memory_order_release);
        return v;
    }

private:
    std::array<T, N> buf_{};
    std::atomic<std::size_t> head_{0};
    std::atomic<std::size_t> tail_{0};
};

} // namespace m09
