// std::function, move_only_function, invoke y bind_front [11/17/20/23]
#include <cassert>
#include <functional>
#include <memory>
#include <string>

struct Calculadora {
    int base = 10;
    int sumar(int x) const { return base + x; }
};

int restar(int a, int b) { return a - b; }

int main() {
    // std::function: borrado de tipo, copiable
    std::function<int(int, int)> op = restar;
    assert(op(5, 3) == 2);
    op = [](int a, int b) { return a * b; };
    assert(op(5, 3) == 15);

    // std::invoke [17]: llamada uniforme a funciones, lambdas y punteros a miembro
    Calculadora c;
    assert(std::invoke(&Calculadora::sumar, c, 5) == 15);
    assert(std::invoke(&Calculadora::base, c) == 10);

    // bind_front [20]: fija los primeros argumentos
    auto menos_diez = std::bind_front(restar, 10);
    assert(menos_diez(3) == 7);

#if defined(__cpp_lib_move_only_function)
    // move_only_function [23]: admite cierres no copiables
    auto p = std::make_unique<int>(42);
    std::move_only_function<int()> f = [q = std::move(p)] { return *q; };
    assert(f() == 42);
    // std::function<int()> g = [q = std::make_unique<int>(1)] { return *q; };  // error
#endif
}
