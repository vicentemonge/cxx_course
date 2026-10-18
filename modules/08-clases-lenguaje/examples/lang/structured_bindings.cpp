// Structured bindings y tipos propios desestructurables [17/20]
#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <tuple>
#include <utility>

// Hacer una clase desestructurable con el protocolo tuple-like
class Rango {
public:
    Rango(int a, int b) : ini_{a}, fin_{b} {}
    template <std::size_t I> int get() const { return I == 0 ? ini_ : fin_; }

private:
    int ini_, fin_;
};
template <> struct std::tuple_size<Rango> : std::integral_constant<std::size_t, 2> {};
template <std::size_t I> struct std::tuple_element<I, Rango> { using type = int; };

std::tuple<int, std::string, double> datos() { return {1, "uno", 1.0}; }

int main() {
    auto [n, s, d] = datos();
    assert(n == 1 && s == "uno" && d == 1.0);

    std::map<std::string, int> m{{"a", 1}};
    if (auto [it, insertado] = m.insert({"b", 2}); insertado) {   // if con inicializador [17]
        assert(it->second == 2);
    }

    int arr[] = {7, 8};
    auto& [x, y] = arr;
    x = 70;
    assert(arr[0] == 70);

    auto [ini, fin] = Rango{3, 9};
    assert(ini == 3 && fin == 9);

    // [20]: los bindings pueden capturarse en lambdas
    auto suma = [ini, fin] { return ini + fin; };
    assert(suma() == 12);
}
