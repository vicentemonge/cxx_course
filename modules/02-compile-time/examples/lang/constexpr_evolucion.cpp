// Evolución de constexpr: C++11 -> 14 -> 20 [11/14/17/20]
#include <algorithm>
#include <array>
#include <cstdio>
#include <numeric>
#include <vector>

// C++11: una sola expresión de retorno
constexpr unsigned long long fact11(unsigned n) { return n <= 1 ? 1 : n * fact11(n - 1); }

// C++14: bucles y variables locales
constexpr unsigned long long fact14(unsigned n) {
    unsigned long long r = 1;
    for (unsigned i = 2; i <= n; ++i) r *= i;
    return r;
}

// C++17: lambdas constexpr
constexpr auto cuadrado = [](int x) { return x * x; };

// C++20: std::vector y algoritmos en compilación (memoria transitoria)
constexpr int suma_primos_hasta(int n) {
    std::vector<int> primos;
    for (int i = 2; i <= n; ++i) {
        bool es = std::none_of(primos.begin(), primos.end(), [i](int p) { return i % p == 0; });
        if (es) primos.push_back(i);
    }
    return std::accumulate(primos.begin(), primos.end(), 0);
}

// C++20: algoritmos constexpr sobre std::array
constexpr std::array<int, 5> ordenado() {
    std::array<int, 5> a{5, 3, 1, 4, 2};
    std::sort(a.begin(), a.end());
    return a;
}

int main() {
    static_assert(fact11(10) == fact14(10));
    static_assert(cuadrado(9) == 81);
    static_assert(suma_primos_hasta(20) == 77);
    static_assert(ordenado() == std::array{1, 2, 3, 4, 5});
    std::printf("20! = %llu\n", fact14(20));
}
