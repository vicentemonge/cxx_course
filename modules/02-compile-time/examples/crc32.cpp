#include "examples/crc32.hpp"
#include <cstdio>

// Calculado en compilación: el valor está en el binario como constante.
constinit const std::uint32_t kCheck = m02::crc32("123456789");

int main() { std::printf("crc32 = 0x%08X\n", static_cast<unsigned>(kCheck)); }
