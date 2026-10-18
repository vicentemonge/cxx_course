// enum class, using enum, to_underlying, literales y UDLs [11/14/20/23]
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <string>
#include <utility>

enum class Color : std::uint8_t { Rojo, Verde, Azul };

const char* nombre(Color c) {
    switch (c) {
        using enum Color;      // [20]: evita repetir Color::
        case Rojo: return "rojo";
        case Verde: return "verde";
        case Azul: return "azul";
    }
    return "?";
}

// Literal definido por el usuario [11]
constexpr long double operator""_km(long double v) { return v * 1000.0L; }

int main() {
    static_assert(std::to_underlying(Color::Azul) == 2);  // [23]
    // int n = Color::Rojo;   // error: enum class no convierte implícitamente

    constexpr auto mascara = 0b1010'0000;   // binario y separador [14]
    constexpr auto millon = 1'000'000;
    static_assert(mascara == 160 && millon == 1000000);

    constexpr auto distancia = 1.5_km;
    static_assert(distancia == 1500.0L);

    // Raw string [11]: útil para regex, JSON o rutas
    std::string json = R"({"clave": "valor\n"})";
    assert(json.find("\\n") != std::string::npos);

    std::printf("%s %s\n", nombre(Color::Verde), json.c_str());
}
