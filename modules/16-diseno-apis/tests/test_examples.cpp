#include <doctest/doctest.h>
#include "examples/embedded/sensor_polimorfismo.hpp"

static_assert(m16::Sensor<m16::Ntc>);
static_assert(m16::Sensor<m16::Termopar>);

TEST_CASE("las tres formas de polimorfismo leen el mismo sensor") {
    m16::Ntc n{.valor = 42};
    CHECK(m16::promedio(n, 3) == 42);
    m16::SensorRef<> r{n};
    CHECK(r.leer() == 42);
    m16::Termopar t;
    m16::ISensor& i = t;
    CHECK(i.leer() == 250);
}
