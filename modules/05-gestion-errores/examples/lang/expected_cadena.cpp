// std::expected: parsing con composición monádica [23]
#include <cassert>
#include <charconv>
#include <expected>
#include <string>
#include <string_view>

enum class ErrorParseo { Vacio, NoNumerico, FueraDeRango };

std::expected<int, ErrorParseo> parsear(std::string_view s) {
    if (s.empty()) return std::unexpected(ErrorParseo::Vacio);
    int v{};
    auto [p, ec] = std::from_chars(s.data(), s.data() + s.size(), v);
    if (ec == std::errc::result_out_of_range) return std::unexpected(ErrorParseo::FueraDeRango);
    if (ec != std::errc{} || p != s.data() + s.size()) return std::unexpected(ErrorParseo::NoNumerico);
    return v;
}

std::expected<int, ErrorParseo> en_rango(int v) {
    if (v < 0 || v > 100) return std::unexpected(ErrorParseo::FueraDeRango);
    return v;
}

std::string describir(ErrorParseo e) {
    switch (e) {
        case ErrorParseo::Vacio: return "vacío";
        case ErrorParseo::NoNumerico: return "no numérico";
        case ErrorParseo::FueraDeRango: return "fuera de rango";
    }
    return "?";
}

int main() {
    auto ok = parsear("42").and_then(en_rango).transform([](int v) { return v * 2; });
    assert(ok && *ok == 84);

    auto mal = parsear("500").and_then(en_rango);
    assert(!mal && mal.error() == ErrorParseo::FueraDeRango);

    // transform_error convierte el tipo de error; value_or da un valor por defecto
    auto texto = parsear("abc").transform_error(describir);
    assert(texto.error() == "no numérico");
    assert(parsear("").value_or(-1) == -1);
}
