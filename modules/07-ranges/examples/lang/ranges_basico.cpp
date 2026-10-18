// Algoritmos de ranges, proyecciones y views [20]
#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

struct Persona {
    std::string nombre;
    int edad;
};

int main() {
    std::vector<Persona> gente{{"Ana", 34}, {"Luis", 19}, {"Eva", 27}, {"Juan", 42}};

    // Proyección: ordenar por un miembro sin escribir comparador
    std::ranges::sort(gente, {}, &Persona::edad);
    assert(gente.front().nombre == "Luis");

    auto it = std::ranges::find(gente, "Eva", &Persona::nombre);
    assert(it != gente.end() && it->edad == 27);

    // Pipeline perezoso: mayores de 25, solo el nombre, los dos primeros
    auto nombres = gente
                 | std::views::filter([](const Persona& p) { return p.edad > 25; })
                 | std::views::transform(&Persona::nombre)
                 | std::views::take(2);
    for (const auto& n : nombres) std::cout << n << ' ';
    std::cout << '\n';

    assert(std::ranges::distance(nombres) == 2);
    assert(std::ranges::max(gente, {}, &Persona::edad).nombre == "Juan");
}
