#include "examples/embedded/trama_a_struct.hpp"
#include <cstdio>

int main() {
    const std::array raw{std::byte{0x02}, std::byte{0x10}, std::byte{0x00},
                         std::byte{0x78}, std::byte{0x56}, std::byte{0x34}, std::byte{0x12}};
    auto c = m15::parsear_cabecera(raw);
    if (!c) return 1;
    std::printf("tipo=%u len=%u seq=0x%08lX\n", c->tipo, c->longitud,
                static_cast<unsigned long>(c->secuencia));
}
