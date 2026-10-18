// Inicialización uniforme, initializer_list, NSDMI y agregados [11/14/17/20]
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

struct Punto {          // agregado con NSDMI [14]
    int x = 0;
    int y = 0;
};

class Widget {
public:
    Widget() = default;
    explicit Widget(int n) : n_{n} {}
    [[nodiscard]] int n() const { return n_; }

private:
    int n_ = 42;        // NSDMI [11]: valor por defecto si ningún constructor lo fija
};

int main() {
    // Llaves frente a paréntesis: initializer_list gana con llaves
    std::vector<int> a(3, 1);  // {1, 1, 1}
    std::vector<int> b{3, 1};  // {3, 1}
    assert(a.size() == 3 && b.size() == 2);

    // Narrowing: con llaves es un error de compilación
    double d = 3.7;
    int i1 = static_cast<int>(d);  // conversión explícita
    // int i2{d};                  // error: narrowing conversion
    (void)i1;

    // Agregados: inicialización con llaves, designada [20] y con paréntesis [20]
    Punto p1{1, 2};
    Punto p2{.y = 5};          // x usa su NSDMI
    Punto p3(7, 8);            // [20]
    assert(p2.x == 0 && p2.y == 5 && p3.x == 7);

    Widget w1;
    Widget w2{7};
    assert(w1.n() == 42 && w2.n() == 7);

    // Most vexing parse: "Widget w3();" declara una función. Con llaves no hay ambigüedad.
    Widget w3{};
    assert(w3.n() == 42);

    std::string s{"hola"};
    std::printf("p1=(%d,%d) s=%s\n", p1.x, p1.y, s.c_str());
}
