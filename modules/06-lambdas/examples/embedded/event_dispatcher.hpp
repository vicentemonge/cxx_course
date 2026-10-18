#pragma once
#include <array>
#include <cstddef>
#include <new>
#include <type_traits>

namespace m06 {

// Invocable con almacenamiento fijo (sin heap). Base para el ejercicio.
template <std::size_t Cap = 16>
class StaticCallback {
public:
    StaticCallback() = default;

    template <class F>
        requires(sizeof(F) <= Cap && std::is_trivially_copyable_v<F> && std::is_invocable_v<F&>)
    StaticCallback(F f) : call_{[](void* p) { (*static_cast<F*>(p))(); }} {
        ::new (static_cast<void*>(buf_.data())) F(f);
    }

    void operator()() { if (call_) call_(buf_.data()); }
    explicit operator bool() const { return call_ != nullptr; }

private:
    alignas(std::max_align_t) std::array<std::byte, Cap> buf_{};
    void (*call_)(void*) = nullptr;
};

template <std::size_t N>
class Dispatcher {
public:
    bool subscribe(StaticCallback<> cb) {
        if (count_ == N) return false;
        slots_[count_++] = cb;
        return true;
    }
    void emit() { for (std::size_t i = 0; i < count_; ++i) slots_[i](); }

private:
    std::array<StaticCallback<>, N> slots_{};
    std::size_t count_ = 0;
};

} // namespace m06
