#include <doctest/doctest.h>
#include "examples/embedded/hal_mock.hpp"

TEST_CASE("LedEstado genera el patrón de pulsos") {
    m18::GpioMock gpio;
    m18::LedEstado led{gpio};
    led.codigo(2);
    for (int i = 0; i < 16; ++i) led.tick();
    const std::vector<bool> ciclo{true, false, true, false, false, false, false, false};
    REQUIRE(gpio.historial.size() == 16);
    for (std::size_t i = 0; i < 16; ++i) CHECK(gpio.historial[i] == ciclo[i % ciclo.size()]);
}

TEST_CASE("Sin código de error el LED queda apagado") {
    m18::GpioMock gpio;
    m18::LedEstado led{gpio};
    led.tick();
    CHECK(gpio.historial == std::vector<bool>{false});
}
