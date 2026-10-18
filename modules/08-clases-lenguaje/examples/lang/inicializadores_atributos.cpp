// if/switch con inicializador, atributos y explicit(bool) [17/20]
#include <cassert>
#include <map>
#include <string>
#include <type_traits>

template <typename T>
struct Envoltorio {
    // explicit solo si la conversión no es implícita [20]
    template <typename U>
    explicit(!std::is_convertible_v<U, T>) Envoltorio(U u) : v(u) {}
    T v;
};

int clasificar(int n) {
    switch (int r = n % 3; r) {    // switch con inicializador [17]
        case 0: return 0;
        case 1: [[fallthrough]];   // [17] caída intencionada sin warning
        case 2: return 1;
        default: return -1;
    }
}

int dividir(int a, int b) {
    if (b == 0) [[unlikely]] return 0;   // [20] pista para el optimizador
    return a / b;
}

int main() {
    std::map<std::string, int> m{{"x", 1}};
    if (auto it = m.find("x"); it != m.end()) {   // it solo vive en el if
        assert(it->second == 1);
    }

    assert(clasificar(3) == 0 && clasificar(4) == 1);
    assert(dividir(6, 0) == 0);

    Envoltorio<long> a = 5;          // int -> long implícito: constructor no explicit
    Envoltorio<std::string> b{"s"};  // const char* -> string: implícito también
    assert(a.v == 5 && b.v == "s");

    [[maybe_unused]] int solo_debug = 0;   // [17] sin warning si no se usa
}
