#pragma once
#include <coroutine>
#include <exception>
#include <utility>

namespace m10 {

// Generador mínimo escrito a mano (std::generator llega en C++23 / GCC 14).
template <class T>
class Generator {
public:
    struct promise_type {
        T current{};
        Generator get_return_object() { return Generator{Handle::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T v) noexcept { current = std::move(v); return {}; }
        void return_void() noexcept {}
        void unhandled_exception() { std::terminate(); }
    };
    using Handle = std::coroutine_handle<promise_type>;

    explicit Generator(Handle h) : h_{h} {}
    Generator(Generator&& o) noexcept : h_{std::exchange(o.h_, {})} {}
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator& operator=(Generator&&) = delete;
    ~Generator() { if (h_) h_.destroy(); }

    bool next() { h_.resume(); return !h_.done(); }
    const T& value() const { return h_.promise().current; }

private:
    Handle h_;
};

inline Generator<unsigned> fibonacci(unsigned n) {
    unsigned a = 0, b = 1;
    for (unsigned i = 0; i < n; ++i) {
        co_yield a;
        a = std::exchange(b, a + b);
    }
}

} // namespace m10
