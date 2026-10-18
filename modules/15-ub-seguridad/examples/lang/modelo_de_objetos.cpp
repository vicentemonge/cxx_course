// Layout, alineación y categorías de tipos · @lifetime @type-design
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>

struct ConPadding {
    std::uint8_t a;    // 1 byte + 3 de padding
    std::uint32_t b;
    std::uint8_t c;    // 1 byte + 3 de padding final
};

struct Reordenado {
    std::uint32_t b;
    std::uint8_t a;
    std::uint8_t c;
};

struct Trivial { int x; float y; };
struct NoTrivial { std::string s; };

int main() {
    static_assert(sizeof(ConPadding) == 12);
    static_assert(sizeof(Reordenado) == 8);     // ordenar por tamaño reduce padding
    static_assert(offsetof(ConPadding, b) == 4);
    static_assert(alignof(ConPadding) == 4);

    static_assert(std::is_trivially_copyable_v<Trivial>);    // copiable con memcpy
    static_assert(!std::is_trivially_copyable_v<NoTrivial>);
    static_assert(std::is_standard_layout_v<Trivial>);        // compatible con C
    static_assert(std::is_aggregate_v<Trivial>);

    // Creación implícita de objetos [20]: memcpy sobre almacenamiento crea un Trivial
    alignas(Trivial) std::byte buf[sizeof(Trivial)];
    Trivial origen{7, 2.5f};
    std::memcpy(buf, &origen, sizeof origen);
    Trivial copia{};
    std::memcpy(&copia, buf, sizeof copia);
    assert(copia.x == 7);

    // Alineación sobre-dimensionada, típica para DMA o líneas de caché
    struct alignas(64) Linea { int v; };
    static_assert(alignof(Linea) == 64 && sizeof(Linea) == 64);
    auto p = std::make_unique<Linea>();          // new respeta la alineación [17]
    assert(reinterpret_cast<std::uintptr_t>(p.get()) % 64 == 0);
}
