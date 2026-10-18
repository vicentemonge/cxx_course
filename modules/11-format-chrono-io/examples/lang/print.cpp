// std::print / std::println [23] y formato de rangos
#include <cstdio>
#include <vector>
#if defined(__has_include) && __has_include(<print>)
#include <print>
#endif
#include <format>

int main() {
#if defined(__cpp_lib_print)
    std::println("hola {}", "mundo");
    std::print("{:>6}\n", 3.5);
#else
    std::printf("std::print no disponible en esta biblioteca (requiere GCC 14+)\n");
#endif
#if defined(__cpp_lib_format_ranges)
    std::vector<int> v{1, 2, 3};
    std::printf("%s\n", std::format("{}", v).c_str());   // [1, 2, 3]
#endif
}
