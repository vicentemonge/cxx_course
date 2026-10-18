// Placement new, construct_at, destroy_at y launder [17/20]
#include <cassert>
#include <cstddef>
#include <memory>
#include <new>
#include <string>

struct Objeto {
    static inline int vivos = 0;
    std::string nombre;
    explicit Objeto(std::string n) : nombre{std::move(n)} { ++vivos; }
    ~Objeto() { --vivos; }
    Objeto(const Objeto&) = delete;
    Objeto& operator=(const Objeto&) = delete;
};

int main() {
    // Almacenamiento estático sin inicializar (pool, buffer en .bss, etc.)
    alignas(Objeto) std::byte almacen[sizeof(Objeto)];

    // construct_at [20]: placement new con nombre claro y usable en constexpr
    Objeto* p = std::construct_at(reinterpret_cast<Objeto*>(almacen), "primero");
    assert(Objeto::vivos == 1 && p->nombre == "primero");
    std::destroy_at(p);                                   // [17]
    assert(Objeto::vivos == 0);

    // Reutilizar el almacenamiento: launder [17] obtiene un puntero válido al nuevo objeto
    ::new (almacen) Objeto{"segundo"};
    Objeto* q = std::launder(reinterpret_cast<Objeto*>(almacen));
    assert(q->nombre == "segundo");
    std::destroy_at(q);
    assert(Objeto::vivos == 0);
}
