// Concepts: definición, sintaxis abreviada, requires y subsunción [20]
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

template <typename T>
concept Numerico = std::integral<T> || std::floating_point<T>;

template <typename T>
concept Hasheable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

template <typename C>
concept Contenedor = requires(C c) {
    typename C::value_type;          // requisito de tipo
    { c.size() } -> std::convertible_to<std::size_t>;
    c.begin();
    c.end();
};

// Cuatro formas equivalentes de restringir
template <typename T> requires Numerico<T> T doble1(T x) { return x * 2; }
template <Numerico T> T doble2(T x) { return x * 2; }
auto doble3(Numerico auto x) { return x * 2; }
template <typename T> T doble4(T x) requires Numerico<T> { return x * 2; }

// Subsunción: se elige la sobrecarga más restringida
template <typename T> requires std::integral<T>
std::string clasificar(T) { return "entero"; }
template <typename T> requires std::integral<T> && std::signed_integral<T>
std::string clasificar(T) { return "entero con signo"; }

template <Contenedor C>
std::size_t tamano(const C& c) { return c.size(); }

int main() {
    assert(doble1(2) == 4 && doble2(2.5) == 5.0 && doble3(3) == 6 && doble4(1) == 2);
    // doble2("x");   // error claro: "x" no satisface Numerico
    assert(clasificar(5u) == "entero");
    assert(clasificar(-5) == "entero con signo");
    static_assert(Hasheable<std::string> && !Hasheable<std::vector<int>>);
    assert(tamano(std::vector{1, 2, 3}) == 3);
}
