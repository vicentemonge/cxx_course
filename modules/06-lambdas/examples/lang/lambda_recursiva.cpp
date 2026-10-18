// Lambdas recursivas: antes con std::function, en C++23 con deducing this
#include <cassert>
#include <functional>

int main() {
    // C++11..20: recursión a través de std::function (coste de borrado de tipo)
    std::function<int(int)> fib_old = [&](int n) { return n < 2 ? n : fib_old(n - 1) + fib_old(n - 2); };
    assert(fib_old(10) == 55);

#if defined(__cpp_explicit_this_parameter)
    // [23]: el propio cierre se recibe como parámetro explícito
    auto fib = [](this auto self, int n) -> int { return n < 2 ? n : self(n - 1) + self(n - 2); };
    assert(fib(10) == 55);
#endif
}
