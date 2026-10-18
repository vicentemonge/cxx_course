// Evaluación perezosa y rangos infinitos [20]
#include <cassert>
#include <ranges>
#include <string_view>
#include <vector>

int main() {
    int evaluaciones = 0;
    auto cuadrados = std::views::iota(1)        // infinito: 1, 2, 3, ...
                   | std::views::transform([&](int x) { ++evaluaciones; return x * x; })
                   | std::views::take_while([](int x) { return x < 50; });

    assert(evaluaciones == 0);                 // nada se ha calculado todavía
    std::vector<int> v;
    for (int x : cuadrados) v.push_back(x);
    assert((v == std::vector{1, 4, 9, 16, 25, 36, 49}));

    // split + transform: tokenizar sin copiar
    std::string_view csv = "rojo,verde,azul";
    std::vector<std::string_view> partes;
    for (auto parte : csv | std::views::split(',')) {
        partes.emplace_back(parte.begin(), parte.end());
    }
    assert(partes.size() == 3 && partes[1] == "verde");

    // reverse, drop, keys
    std::vector<int> n{1, 2, 3, 4, 5};
    auto r = n | std::views::reverse | std::views::drop(1);
    assert(*r.begin() == 4);
}
