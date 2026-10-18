#include "examples/embedded/sensor_polimorfismo.hpp"
#include <cinttypes>
#include <cstdio>

int main() {
    m16::Termopar t;
    m16::ISensor& is = t;
    m16::Ntc n;
    m16::SensorRef<> ref{n};
    std::printf("virtual=%" PRId32 " concept=%" PRId32 " erasure=%" PRId32 "\n", is.leer(),
                m16::promedio(n, 4), ref.leer());
}
