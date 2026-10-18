#include "examples/embedded/raii_uart.hpp"
#include <cstdio>

int main() {
    m01::Uart a{1, {.baud = 9600, .parity = m01::Parity::Even}};
    m01::Uart b = std::move(a);
    std::printf("a open=%d, b open=%d\n", a.is_open(), b.is_open());
}
