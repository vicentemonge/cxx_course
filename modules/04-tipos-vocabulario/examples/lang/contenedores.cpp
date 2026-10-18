// Novedades en contenedores y utilidades [17/20/23]
#include <array>
#include <cassert>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

int main() {
    std::map<std::string, int> m;
    m.try_emplace("a", 1);              // [17] no construye si la clave ya existe
    m.try_emplace("a", 99);
    m.insert_or_assign("b", 2);         // [17]
    assert(m["a"] == 1 && m.contains("b"));   // contains [20]

    for (const auto& [clave, valor] : m) {    // structured bindings [17]
        assert(!clave.empty() && valor > 0);
    }

    std::vector<int> v{1, 2, 3, 4, 5, 6};
    auto borrados = std::erase_if(v, [](int x) { return x % 2 == 0; });   // [20]
    assert(borrados == 3 && v == (std::vector{1, 3, 5}));
    assert(std::ssize(v) == 3);         // tamaño con signo [20]

    auto arr = std::to_array({1, 2, 3});   // [20] deduce tipo y tamaño
    static_assert(std::is_same_v<decltype(arr), std::array<int, 3>>);

    // make_from_tuple [17]: construir un objeto con los elementos de una tupla
    auto s = std::make_from_tuple<std::string>(std::tuple{3, 'x'});
    assert(s == "xxx");
}
