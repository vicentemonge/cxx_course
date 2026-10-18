// to_chars / from_chars: conversiones rápidas, sin locale ni excepciones [17]
#include <array>
#include <cassert>
#include <charconv>
#include <string_view>
#include <system_error>

int main() {
    std::array<char, 32> buf{};

    auto [fin, ec] = std::to_chars(buf.data(), buf.data() + buf.size(), 255, 16);
    assert(ec == std::errc{});
    assert(std::string_view(buf.data(), static_cast<std::size_t>(fin - buf.data())) == "ff");

    int v{};
    std::string_view s = "1234xyz";
    auto r = std::from_chars(s.data(), s.data() + s.size(), v);
    assert(v == 1234);
    assert(r.ptr == s.data() + 4);           // se detiene en el primer carácter no válido

    double d{};
    std::string_view sd = "2.5e3";
    std::from_chars(sd.data(), sd.data() + sd.size(), d);
    assert(d == 2500.0);

    signed char pequeno{};
    auto overflow = std::from_chars(s.data(), s.data() + 4, pequeno);   // 1234 no cabe en 8 bits
    assert(overflow.ec == std::errc::result_out_of_range);
}
