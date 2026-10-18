#include "examples/embedded/event_dispatcher.hpp"
#include <cstdio>

int main() {
    int counter = 0;
    m06::Dispatcher<4> d;
    d.subscribe([&counter] { ++counter; });
    d.subscribe([&counter] { counter += 10; });
    d.emit();
    std::printf("counter=%d\n", counter);
}
