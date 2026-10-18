// std::variant, std::visit y el patrón overloaded [17]
#include <cassert>
#include <cstdio>
#include <string>
#include <variant>
#include <vector>

struct Circulo { double r; };
struct Rectangulo { double w, h; };
struct Triangulo { double b, h; };
using Figura = std::variant<Circulo, Rectangulo, Triangulo>;

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

double area(const Figura& f) {
    return std::visit(overloaded{
        [](const Circulo& c) { return 3.14159 * c.r * c.r; },
        [](const Rectangulo& r) { return r.w * r.h; },
        [](const Triangulo& t) { return t.b * t.h / 2; }}, f);
}

int main() {
    std::vector<Figura> figuras{Circulo{1}, Rectangulo{2, 3}, Triangulo{4, 5}};
    double total = 0;
    for (const auto& f : figuras) total += area(f);
    std::printf("área total = %.2f\n", total);

    std::variant<int, std::string> v = 5;
    assert(std::holds_alternative<int>(v));
    v = "texto";
    assert(std::get_if<int>(&v) == nullptr);
    assert(std::get<std::string>(v) == "texto");
    assert(v.index() == 1);
}
