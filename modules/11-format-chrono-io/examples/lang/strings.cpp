// Novedades en std::string [17/20/23]
#include <cassert>
#include <string>
#include <string_view>

int main() {
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    auto s = "ruta/al/fichero.txt"s;       // std::string [14]
    auto sv = "solo vista"sv;              // std::string_view [17]

    assert(s.starts_with("ruta"));         // [20]
    assert(s.ends_with(".txt"));
    assert(s.contains("al/"));             // [23]
    assert(sv.size() == 10);

    // Literal con '\0' embebido: el sufijo s conserva toda la longitud
    auto con_nulo = "a\0b"s;
    assert(con_nulo.size() == 3);

    // SSO: cadenas cortas no reservan memoria dinámica (capacidad mínima > 0)
    std::string corta;
    assert(corta.capacity() >= 15);

#if defined(__cpp_lib_string_resize_and_overwrite)
    // resize_and_overwrite [23]: rellenar sin inicializar a cero primero
    std::string buf;
    buf.resize_and_overwrite(5, [](char* p, std::size_t n) {
        for (std::size_t i = 0; i < n; ++i) p[i] = static_cast<char>('a' + i);
        return n;
    });
    assert(buf == "abcde");
#endif
}
