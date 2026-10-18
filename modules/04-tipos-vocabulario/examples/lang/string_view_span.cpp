// Vistas no propietarias: string_view [17] y span [20]
#include <array>
#include <cassert>
#include <numeric>
#include <span>
#include <string>
#include <string_view>
#include <vector>

// Acepta std::string, literales y string_view sin copiar
std::size_t contar(std::string_view s, char c) {
    std::size_t n = 0;
    for (char x : s) n += (x == c);
    return n;
}

// Acepta vector, array y arrays C sin plantillas
int suma(std::span<const int> datos) { return std::accumulate(datos.begin(), datos.end(), 0); }

// Dangling: la vista apunta a memoria liberada. Clang lo detecta (-Wreturn-stack-address).
// std::string_view peligroso() {
//     std::string temporal = "se destruye al salir";
//     return temporal;
// }

int main() {
    assert(contar("banana", 'a') == 3);
    std::string s = "abracadabra";
    std::string_view sv = s;
    assert(sv.substr(0, 4) == "abra");   // substr sin asignación de memoria

    std::vector<int> v{1, 2, 3, 4};
    std::array<int, 3> a{10, 20, 30};
    int c[] = {100, 200};
    assert(suma(v) == 10 && suma(a) == 60 && suma(c) == 300);

    std::span<int> vista{v};
    assert(suma(vista.subspan(1, 2)) == 5);
    std::span<int, 3> fija{a};          // extensión estática: tamaño en el tipo
    static_assert(sizeof(fija) == sizeof(int*));
}
