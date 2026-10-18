// Coste de abstracciones: llamada directa, plantilla, virtual y std::function · @performance
// El resultado interesante está en el ensamblador: compilar con -O2 en Compiler Explorer.
#include <cassert>
#include <functional>

struct Base { virtual int f(int x) const = 0; virtual ~Base() = default; };
struct Impl final : Base { int f(int x) const override { return x * 2; } };

int directa(int x) { return x * 2; }

template <typename F>
int con_plantilla(F f, int x) { return f(x); }          // se inlinea por completo

int con_virtual(const Base& b, int x) { return b.f(x); } // despacho indirecto salvo devirtualización

int con_function(const std::function<int(int)>& f, int x) { return f(x); }   // borrado de tipo

int main() {
    Impl impl;
    auto lambda = [](int x) { return x * 2; };
    int r1 = directa(21);
    int r2 = con_plantilla(lambda, 21);
    int r3 = con_virtual(impl, 21);       // `final` permite devirtualizar si el tipo es conocido
    int r4 = con_function(lambda, 21);
    assert(r1 == 42 && r2 == 42 && r3 == 42 && r4 == 42);
}
