// Operador <=> y comparaciones por defecto [20]
#include <cassert>
#include <cctype>
#include <compare>
#include <set>
#include <string>

struct Fecha {
    int anio, mes, dia;
    auto operator<=>(const Fecha&) const = default;   // genera <, <=, >, >=, ==, !=
};

// Ordenación personalizada: comparación sin distinguir mayúsculas
struct Nombre {
    std::string s;
    std::weak_ordering operator<=>(const Nombre& o) const {
        for (std::size_t i = 0; i < s.size() && i < o.s.size(); ++i) {
            auto a = std::tolower(static_cast<unsigned char>(s[i]));
            auto b = std::tolower(static_cast<unsigned char>(o.s[i]));
            if (a != b) return a <=> b;
        }
        return s.size() <=> o.s.size();
    }
    bool operator==(const Nombre& o) const { return (*this <=> o) == 0; }
};

int main() {
    assert((Fecha{2024, 5, 1} < Fecha{2024, 6, 1}));
    assert((Fecha{2024, 5, 1} == Fecha{2024, 5, 1}));

    assert((Nombre{"Ana"} == Nombre{"ANA"}));
    assert((Nombre{"ana"} < Nombre{"Bea"}));

    std::set<Fecha> fechas{{2025, 1, 1}, {2023, 1, 1}};
    assert(fechas.begin()->anio == 2023);

    auto r = 1.0 <=> 2.0;   // partial_ordering (NaN no es comparable)
    assert(r < 0);
}
