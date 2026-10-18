// PIMPL: ocultar la implementación para estabilizar ABI y reducir dependencias · @abi
// En un proyecto real, la clase Impl y los miembros fuera de línea viven en el .cpp.
#include <cassert>
#include <memory>
#include <string>
#include <vector>

// ---- cabecera pública (lo que ven los clientes) ----
class Registro {
public:
    Registro();
    ~Registro();                                  // definido donde Impl está completo
    Registro(Registro&&) noexcept;
    Registro& operator=(Registro&&) noexcept;
    Registro(const Registro&) = delete;
    Registro& operator=(const Registro&) = delete;

    void anotar(std::string linea);
    [[nodiscard]] std::size_t tamano() const;

private:
    struct Impl;                                  // tipo incompleto
    std::unique_ptr<Impl> impl_;
};

// ---- fichero .cpp (cambiar esto no recompila a los clientes) ----
struct Registro::Impl {
    std::vector<std::string> lineas;
    std::size_t bytes = 0;
};

Registro::Registro() : impl_{std::make_unique<Impl>()} {}
Registro::~Registro() = default;
Registro::Registro(Registro&&) noexcept = default;
Registro& Registro::operator=(Registro&&) noexcept = default;

void Registro::anotar(std::string linea) {
    impl_->bytes += linea.size();
    impl_->lineas.push_back(std::move(linea));
}
std::size_t Registro::tamano() const { return impl_->lineas.size(); }

int main() {
    Registro r;
    r.anotar("arranque");
    r.anotar("ok");
    Registro movido = std::move(r);
    assert(movido.tamano() == 2);
    static_assert(sizeof(Registro) == sizeof(void*));   // el layout público no cambia nunca
}
