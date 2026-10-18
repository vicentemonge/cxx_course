// Deducing this / parámetro objeto explícito [23]
#include <cassert>
#include <string>
#include <utility>

#if defined(__cpp_explicit_this_parameter)
class Texto {
public:
    explicit Texto(std::string s) : s_{std::move(s)} {}

    // Una sola función reemplaza las sobrecargas &, const& y &&
    template <typename Self>
    auto&& valor(this Self&& self) { return std::forward<Self>(self).s_; }

private:
    std::string s_;
};

// CRTP sin CRTP: la base conoce el tipo derivado a través de self
struct Imprimible {
    std::string describir(this const auto& self) { return "[" + self.nombre() + "]"; }
};
struct Sensor : Imprimible {
    std::string nombre() const { return "sensor"; }
};
#endif

int main() {
#if defined(__cpp_explicit_this_parameter)
    Texto t{"hola"};
    t.valor() += "!";
    assert(t.valor() == "hola!");
    const Texto& ct = t;
    static_assert(std::is_same_v<decltype(ct.valor()), const std::string&>);
    std::string movido = std::move(t).valor();
    assert(movido == "hola!");

    assert(Sensor{}.describir() == "[sensor]");
#endif
}
