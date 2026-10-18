// noexcept como especificador, operador y parte del tipo; [[nodiscard]] [11/17/20]
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

void segura() noexcept {}
void insegura() {}

template <typename T>
void intercambiar(T& a, T& b) noexcept(std::is_nothrow_move_constructible_v<T>) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

[[nodiscard("el código de error debe comprobarse")]] int operacion() { return 0; }

struct [[nodiscard]] Resultado { bool ok; };   // nodiscard en el tipo completo
Resultado probar() { return {true}; }

int main() {
    static_assert(noexcept(segura()));            // noexcept como operador
    static_assert(!noexcept(insegura()));

    // Desde C++17 noexcept forma parte del tipo de función
    using FnNoexcept = void (*)() noexcept;
    FnNoexcept f = segura;
    // FnNoexcept g = insegura;   // error: pierde la garantía noexcept
    f();

    int a = 1, b = 2;
    intercambiar(a, b);
    static_assert(noexcept(intercambiar(a, b)));
    assert(a == 2 && b == 1);

    // operacion();               // warning: valor descartado
    [[maybe_unused]] int rc = operacion();
    assert(probar().ok);
}
