// std::error_code con una categoría propia [11]
#include <cassert>
#include <cstdio>
#include <string>
#include <system_error>

enum class ErrorRed { Ok = 0, Timeout = 1, Rechazado = 2 };

class CategoriaRed : public std::error_category {
public:
    const char* name() const noexcept override { return "red"; }
    std::string message(int ev) const override {
        switch (static_cast<ErrorRed>(ev)) {
            case ErrorRed::Ok: return "ok";
            case ErrorRed::Timeout: return "timeout";
            case ErrorRed::Rechazado: return "conexión rechazada";
        }
        return "desconocido";
    }
};

const std::error_category& categoria_red() {
    static const CategoriaRed c;
    return c;
}

std::error_code make_error_code(ErrorRed e) { return {static_cast<int>(e), categoria_red()}; }

template <> struct std::is_error_code_enum<ErrorRed> : std::true_type {};

std::error_code conectar(bool falla) { return falla ? ErrorRed::Timeout : ErrorRed::Ok; }

int main() {
    std::error_code ec = conectar(true);
    assert(ec);                                  // distinto de cero = error
    assert(ec == ErrorRed::Timeout);
    std::printf("%s: %s\n", ec.category().name(), ec.message().c_str());
    assert(!conectar(false));
}
