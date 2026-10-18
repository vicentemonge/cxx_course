// Type erasure al estilo Sean Parent: polimorfismo sin herencia en los tipos de usuario
// · @type-design @value-sem
#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Tipos de usuario: no heredan de nada
struct Circulo { double r; };
struct Cuadrado { double lado; };
double area(const Circulo& c) { return 3.0 * c.r * c.r; }
double area(const Cuadrado& c) { return c.lado * c.lado; }
std::string nombre(const Circulo&) { return "círculo"; }
std::string nombre(const Cuadrado&) { return "cuadrado"; }

class Figura {
public:
    template <typename T>
    Figura(T x) : self_{std::make_unique<Modelo<T>>(std::move(x))} {}

    // Semántica de valor: copiable a pesar del polimorfismo interno
    Figura(const Figura& o) : self_{o.self_->clonar()} {}
    Figura& operator=(const Figura& o) { return *this = Figura{o}; }
    Figura(Figura&&) noexcept = default;
    Figura& operator=(Figura&&) noexcept = default;
    ~Figura() = default;

    friend double area(const Figura& f) { return f.self_->area(); }
    friend std::string nombre(const Figura& f) { return f.self_->nombre(); }

private:
    struct Concepto {
        virtual ~Concepto() = default;
        virtual std::unique_ptr<Concepto> clonar() const = 0;
        virtual double area() const = 0;
        virtual std::string nombre() const = 0;
    };
    template <typename T>
    struct Modelo final : Concepto {
        explicit Modelo(T x) : dato{std::move(x)} {}
        std::unique_ptr<Concepto> clonar() const override { return std::make_unique<Modelo>(*this); }
        double area() const override { return ::area(dato); }
        std::string nombre() const override { return ::nombre(dato); }
        T dato;
    };
    std::unique_ptr<Concepto> self_;
};

int main() {
    std::vector<Figura> figuras{Circulo{1}, Cuadrado{2}};
    figuras.push_back(figuras[0]);   // copia profunda
    double total = 0;
    for (const auto& f : figuras) total += area(f);
    assert(total == 3.0 + 4.0 + 3.0);
    assert(nombre(figuras[1]) == "cuadrado");
}
