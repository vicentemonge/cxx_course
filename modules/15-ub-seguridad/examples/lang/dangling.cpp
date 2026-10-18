// Dangling: patrones de riesgo y alternativas seguras · @lifetime @safety
#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#if defined(__clang__)
#define LIFETIMEBOUND [[clang::lifetimebound]]
#else
#define LIFETIMEBOUND
#endif

// lifetimebound permite a Clang avisar si el resultado sobrevive al argumento
const std::string& mayor(const std::string& a LIFETIMEBOUND, const std::string& b LIFETIMEBOUND) {
    return a.size() >= b.size() ? a : b;
}

// Alternativa segura cuando el llamante puede pasar temporales: devolver por valor
std::string mayor_valor(std::string_view a, std::string_view b) {
    return std::string{a.size() >= b.size() ? a : b};
}

int main() {
    // 1. Referencia a temporal: "const auto& r = mayor(std::string{"a"}, "bb");" queda colgando
    std::string x = "corto", y = "más largo";
    const auto& r = mayor(x, y);   // correcto: x e y siguen vivos
    assert(r == y);
    assert(mayor_valor("a", "bb") == "bb");

    // 2. Invalidación de iteradores: push_back puede reubicar
    std::vector<int> v{1, 2, 3};
    v.reserve(v.size() + 1);       // garantiza que no hay reubicación
    int* p = &v[0];
    v.push_back(4);
    assert(*p == 1);

    // 3. Lambda que captura por referencia y sobrevive al ámbito
    std::function<int()> f;
    {
        int local = 42;
        f = [local] { return local; };   // por valor; con [&local] sería dangling
    }
    assert(f() == 42);

    // 4. operator[] de map dentro de una expresión que también inserta: copiar primero
    std::map<int, std::string> m{{1, "uno"}};
    std::string copia = m[1];
    m[2] = copia;
    assert(m.size() == 2);
}
