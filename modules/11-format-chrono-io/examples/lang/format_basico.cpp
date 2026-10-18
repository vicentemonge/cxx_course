// std::format: especificadores y formatters propios [20]
#include <cassert>
#include <cstdio>
#include <format>
#include <string>
#include <vector>

struct Punto { int x, y; };

template <>
struct std::formatter<Punto> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Punto& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};

int main() {
    assert(std::format("{} + {} = {}", 2, 3, 5) == "2 + 3 = 5");
    assert(std::format("{1} {0}", "mundo", "hola") == "hola mundo");   // índices
    assert(std::format("[{:>5}]", 42) == "[   42]");                    // alineación
    assert(std::format("[{:*^7}]", "ab") == "[**ab***]");               // relleno centrado
    assert(std::format("{:#x} {:08b}", 255, 5) == "0xff 00000101");     // bases
    assert(std::format("{:.3f}", 3.14159) == "3.142");                  // precisión
    assert(std::format("{:+}", 7) == "+7");
    assert(std::format("{}", Punto{1, 2}) == "(1, 2)");

    // La cadena de formato se comprueba en compilación:
    // std::format("{:d}", "texto");   // error de compilación
    std::printf("%s\n", std::format("{:<10}|{:>8.2f}", "total", 12.5).c_str());
}
