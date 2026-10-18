// La misma restricción con SFINAE [11/17] y con concepts [20]
#include <cassert>
#include <string>
#include <type_traits>
#include <utility>

// --- SFINAE con enable_if ---
template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
std::string tipo_sfinae(T) { return "aritmético"; }

template <typename T, std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
std::string tipo_sfinae(T) { return "otro"; }

// --- Detection idiom con void_t: ¿tiene T un método size()? ---
template <typename, typename = void>
struct tiene_size : std::false_type {};
template <typename T>
struct tiene_size<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};

// --- Lo mismo con concepts ---
template <typename T>
std::string tipo_concepts(T) {
    if constexpr (std::is_arithmetic_v<T>) return "aritmético";
    else return "otro";
}

template <typename T>
concept TieneSize = requires(T t) { t.size(); };

int main() {
    assert(tipo_sfinae(1) == "aritmético" && tipo_sfinae(std::string{}) == "otro");
    assert(tipo_concepts(1.0) == "aritmético");
    static_assert(tiene_size<std::string>::value && !tiene_size<int>::value);
    static_assert(TieneSize<std::string> && !TieneSize<int>);
}
