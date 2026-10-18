#include "examples/embedded/q15.hpp"
#include <cstdio>

int main() {
    using m17::Q15;
    Q15 ganancia = Q15::desde_float(0.75f);
    Q15 muestra = Q15::desde_float(-0.5f);
    Q15 y = ganancia * muestra;
    std::printf("0.75 * -0.5 = %.4f (raw %d)\n", static_cast<double>(y.a_float()), y.raw());
}
