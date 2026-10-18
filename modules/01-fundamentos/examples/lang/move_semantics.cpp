// Categorías de valor, move, forward y copy elision [11/17]
#include <cassert>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

struct Traza {
    static inline int copias = 0;
    static inline int movimientos = 0;
    std::string dato;

    explicit Traza(std::string d) : dato{std::move(d)} {}
    Traza(const Traza& o) : dato{o.dato} { ++copias; }
    Traza(Traza&& o) noexcept : dato{std::move(o.dato)} { ++movimientos; }
    Traza& operator=(const Traza&) = default;
    Traza& operator=(Traza&&) noexcept = default;
    ~Traza() = default;

    static void reset() { copias = movimientos = 0; }
};

Traza fabrica() { return Traza{"prvalue"}; }  // copy elision garantizada [17]

void consume(const Traza&) { std::puts("  consume(const&)"); }
void consume(Traza&&) { std::puts("  consume(&&)"); }

// Perfect forwarding: conserva la categoría de valor del argumento
template <typename T>
void reenvia(T&& t) { consume(std::forward<T>(t)); }

int main() {
    Traza::reset();
    Traza a = fabrica();
    assert(Traza::copias == 0 && Traza::movimientos == 0);

    Traza b = a;               // copia
    Traza c = std::move(a);    // movimiento: a queda en estado válido pero no especificado
    assert(Traza::copias == 1 && Traza::movimientos == 1);

    std::puts("forwarding:");
    reenvia(b);                // lvalue -> const&
    reenvia(std::move(c));     // xvalue -> &&

    // noexcept en el constructor de movimiento permite a vector mover al crecer
    Traza::reset();
    std::vector<Traza> v;
    for (int i = 0; i < 8; ++i) v.emplace_back("x");
    std::printf("al crecer: copias=%d movimientos=%d\n", Traza::copias, Traza::movimientos);
    assert(Traza::copias == 0);
}
