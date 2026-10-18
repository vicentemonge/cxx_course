// if constexpr como sustituto de tag dispatching y SFINAE [17]
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
std::string describir(const T& v) {
    if constexpr (std::is_same_v<T, std::string>) {
        return "string(" + v + ")";
    } else if constexpr (std::is_integral_v<T>) {
        return "int(" + std::to_string(v) + ")";
    } else if constexpr (requires { v.size(); }) {   // requires-expression inline [20]
        return "contenedor de " + std::to_string(v.size());
    } else {
        // La rama descartada no se instancia: esto solo falla si se usa con otro tipo
        static_assert(sizeof(T) == 0, "tipo no soportado");
    }
}

int main() {
    assert(describir(std::string{"a"}) == "string(a)");
    assert(describir(7) == "int(7)");
    assert(describir(std::vector<int>{1, 2, 3}) == "contenedor de 3");
}
