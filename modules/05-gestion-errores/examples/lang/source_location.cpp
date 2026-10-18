// std::source_location: trazas sin macros __FILE__/__LINE__ [20]
#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <source_location>
#include <string_view>

void log(std::string_view msg, std::source_location loc = std::source_location::current()) {
    std::printf("%s:%" PRIuLEAST32 " [%s] %.*s\n", loc.file_name(), loc.line(),
                loc.function_name(), static_cast<int>(msg.size()), msg.data());
}

std::uint_least32_t linea_actual(std::source_location loc = std::source_location::current()) {
    return loc.line();
}

int main() {
    log("arrancando");
    auto l = linea_actual();
    assert(l == __LINE__ - 1);   // el argumento por defecto se evalúa en el punto de llamada
}
