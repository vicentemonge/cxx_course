#include "examples/embedded/ticks.hpp"
#include <cstdio>

int main() {
    std::uint32_t inicio = 0xFFFF'FF00u;
    std::uint32_t ahora = 0xFFFF'FF10u;   // 0x10 ticks después; inicio + 0x150 da la vuelta
    std::printf("expirado=%d expirado_mal=%d\n", m15::expirado(ahora, inicio, 0x150u),
                m15::expirado_mal(ahora, inicio, 0x150u));
}
