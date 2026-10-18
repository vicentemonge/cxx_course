// std::generator [23]: generadores perezosos con la biblioteca estándar
#include <cassert>
#include <cstdio>
#if defined(__has_include) && __has_include(<generator>)
#include <generator>
#endif
#include <ranges>
#include <vector>

#if defined(__cpp_lib_generator)
std::generator<int> primos() {
    for (int n = 2;; ++n) {
        bool es = true;
        for (int d = 2; d * d <= n; ++d) if (n % d == 0) { es = false; break; }
        if (es) co_yield n;
    }
}
#endif

int main() {
#if defined(__cpp_lib_generator)
    // std::generator es un range: se combina con views
    std::vector<int> v;
    for (int p : primos() | std::views::take(5)) v.push_back(p);
    assert((v == std::vector{2, 3, 5, 7, 11}));
    std::printf("std::generator disponible\n");
#else
    std::printf("std::generator no disponible en esta biblioteca (requiere GCC 14+)\n");
#endif
}
