// Exponer una clase C++ como API en C (para Rust, Python o firmware en C) · @interop @abi
#include <cassert>
#include <cstddef>
#include <new>
#include <vector>

// ---- implementación C++ ----
namespace detail {
class Filtro {
public:
    explicit Filtro(std::size_t n) : ventana_(n, 0.0) {}
    double procesar(double x) {
        suma_ += x - ventana_[pos_];
        ventana_[pos_] = x;
        pos_ = (pos_ + 1) % ventana_.size();
        return suma_ / static_cast<double>(ventana_.size());
    }

private:
    std::vector<double> ventana_;
    std::size_t pos_ = 0;
    double suma_ = 0;
};
} // namespace detail

// ---- API C: tipo opaco, propiedad explícita, sin excepciones que crucen la frontera ----
extern "C" {
typedef struct filtro filtro_t;

filtro_t* filtro_crear(size_t n) {
    if (n == 0) return nullptr;
    auto* f = new (std::nothrow) detail::Filtro(n);
    return reinterpret_cast<filtro_t*>(f);
}
void filtro_destruir(filtro_t* f) { delete reinterpret_cast<detail::Filtro*>(f); }
double filtro_procesar(filtro_t* f, double x) { return reinterpret_cast<detail::Filtro*>(f)->procesar(x); }
}

int main() {
    filtro_t* f = filtro_crear(4);
    assert(f != nullptr);
    double y = 0;
    for (int i = 0; i < 4; ++i) y = filtro_procesar(f, 8.0);
    assert(y == 8.0);
    filtro_destruir(f);
    assert(filtro_crear(0) == nullptr);
}
