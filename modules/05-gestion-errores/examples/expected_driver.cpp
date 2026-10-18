#include "examples/expected_driver.hpp"
#include <cstdio>

int main() {
    m05::Sensor s;
    if (auto v = m05::bring_up(s, 100)) std::printf("lectura=%d\n", *v);
    else std::printf("error=%d\n", static_cast<int>(v.error()));
}
