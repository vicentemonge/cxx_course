// consteval, constinit e if consteval [20/23]
#include <cassert>
#include <cstdio>

consteval int al_cubo(int x) { return x * x * x; }   // solo en compilación

constexpr int doble(int x) {
#if defined(__cpp_if_consteval)
    if consteval { return x + x; }   // [23] rama de compilación
    else { return x * 2; }           // rama de runtime
#else
    return x * 2;
#endif
}

constinit int contador = al_cubo(3);   // inicialización estática garantizada, pero mutable

int main(int argc, char**) {
    static_assert(al_cubo(2) == 8);
    // int n = al_cubo(argc);   // error: argc no es constante
    contador += 1;
    assert(contador == 28);
    assert(doble(argc) == 2 * argc);
    std::printf("contador=%d\n", contador);
}
