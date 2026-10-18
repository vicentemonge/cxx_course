#include <doctest/doctest.h>
#include "examples/embedded/event_dispatcher.hpp"

TEST_CASE("Dispatcher invoca todas las suscripciones") {
    int n = 0;
    m06::Dispatcher<2> d;
    CHECK(d.subscribe([&n] { ++n; }));
    CHECK(d.subscribe([&n] { ++n; }));
    CHECK_FALSE(d.subscribe([&n] { ++n; }));
    d.emit();
    CHECK(n == 2);
}
