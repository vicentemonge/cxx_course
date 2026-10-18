// Variadic templates, fold expressions e index_sequence [11/14/17]
#include <cassert>
#include <cstddef>
#include <iostream>
#include <tuple>
#include <utility>

template <typename... Ts>
auto suma(Ts... xs) { return (xs + ... + 0); }          // fold binario a la derecha

template <typename... Ts>
bool todos(Ts... xs) { return (... && xs); }            // fold unario a la izquierda

template <typename... Ts>
void imprimir(const Ts&... xs) {
    ((std::cout << xs << ' '), ...);                    // fold sobre el operador coma
    std::cout << '\n';
}

// Recorrer una tupla con index_sequence [14]
template <typename Tuple, std::size_t... I>
void imprimir_tupla_impl(const Tuple& t, std::index_sequence<I...>) { imprimir(std::get<I>(t)...); }

template <typename... Ts>
void imprimir_tupla(const std::tuple<Ts...>& t) {
    imprimir_tupla_impl(t, std::index_sequence_for<Ts...>{});
}

int main() {
    assert(suma(1, 2, 3, 4) == 10);
    assert(todos(true, 1, 'a'));
    assert(!todos(true, 0));
    imprimir("pack:", 1, 2.5, 'c');
    imprimir_tupla(std::tuple{"tupla:", 7, 3.14});
    std::apply([](auto... xs) { imprimir("apply:", xs...); }, std::tuple{1, 2, 3});  // [17]
}
