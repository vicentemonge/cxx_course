#include "examples/embedded/hal_mock.hpp"
#include <cstdio>

int main() {
    m18::GpioMock gpio;
    m18::LedEstado led{gpio};
    led.codigo(2);
    for (int i = 0; i < 8; ++i) led.tick();
    for (bool b : gpio.historial) std::printf("%c", b ? '#' : '.');
    std::printf("\n");
}
