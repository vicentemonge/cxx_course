// Lambdas genéricas [14], con parámetros template [20] y constexpr [17]
#include <cassert>
#include <concepts>
#include <string>
#include <type_traits>
#include <vector>

int main() {
    auto suma = [](auto a, auto b) { return a + b; };            // [14]
    assert(suma(1, 2) == 3);
    assert(suma(std::string{"a"}, "b") == "ab");

    // [20]: lista de parámetros template para nombrar el tipo
    auto tamano = []<typename T>(const std::vector<T>& v) { return v.size() * sizeof(T); };
    assert(tamano(std::vector<int>{1, 2}) == 2 * sizeof(int));

    // Con concepts
    auto mitad = [](std::integral auto n) { return n / 2; };
    assert(mitad(9) == 4);

    // constexpr implícito [17]
    constexpr auto cuadrado = [](int n) { return n * n; };
    static_assert(cuadrado(5) == 25);

    // Lambdas sin estado: construibles por defecto y usables en decltype [20]
    using Comparador = decltype([](int a, int b) { return a > b; });
    Comparador cmp;
    assert(cmp(2, 1));

    // IIFE para inicializar una const con lógica compleja
    const int valor = [] {
        int r = 0;
        for (int i = 1; i <= 4; ++i) r += i;
        return r;
    }();
    assert(valor == 10);
}
