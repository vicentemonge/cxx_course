// std::optional y sus operaciones monádicas [17/23]
#include <cassert>
#include <charconv>
#include <optional>
#include <string>
#include <string_view>

std::optional<int> a_entero(std::string_view s) {
    int v{};
    auto [p, ec] = std::from_chars(s.data(), s.data() + s.size(), v);
    if (ec != std::errc{} || p != s.data() + s.size()) return std::nullopt;
    return v;
}

std::optional<int> positivo(int v) { return v > 0 ? std::optional{v} : std::nullopt; }

int main() {
    // Estilo clásico [17]
    auto o = a_entero("42");
    assert(o.has_value() && *o == 42);
    assert(a_entero("x").value_or(-1) == -1);

    // Composición [23]: and_then encadena, transform mapea, or_else da alternativa
    auto r = a_entero("21")
                 .and_then(positivo)
                 .transform([](int v) { return v * 2; })
                 .transform([](int v) { return std::to_string(v); });
    assert(r == "42");

    auto fallo = a_entero("-3").and_then(positivo).or_else([] { return std::optional{0}; });
    assert(fallo == 0);
}
