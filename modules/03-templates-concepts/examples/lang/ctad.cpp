// Class Template Argument Deduction y guías de deducción [17/20]
#include <array>
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
struct Caja {
    T valor;
    explicit Caja(T v) : valor{v} {}
};

// Guía de deducción: un literal de cadena se guarda como std::string
Caja(const char*) -> Caja<std::string>;

template <typename T, typename U>
struct Par {   // agregado: CTAD para agregados [20]
    T primero;
    U segundo;
};

int main() {
    std::vector v{1, 2, 3};           // vector<int>
    std::array a{1.0, 2.0};           // array<double, 2>
    std::pair p{1, 'x'};              // pair<int, char>
    static_assert(std::is_same_v<decltype(v), std::vector<int>>);
    static_assert(std::is_same_v<decltype(a), std::array<double, 2>>);
    static_assert(std::is_same_v<decltype(p), std::pair<int, char>>);

    Caja c1{3.5};
    Caja c2{"texto"};
    static_assert(std::is_same_v<decltype(c1), Caja<double>>);
    static_assert(std::is_same_v<decltype(c2), Caja<std::string>>);

    Par par{1, 2.0};
    static_assert(std::is_same_v<decltype(par), Par<int, double>>);
    assert(c2.valor.size() == 5);
}
