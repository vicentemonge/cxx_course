// Capturas: valor, referencia, mutable, init-capture y *this [11/14/17]
#include <cassert>
#include <memory>
#include <string>
#include <utility>

struct Contador {
    int n = 0;
    auto incrementador() { return [this] { ++n; }; }           // captura el puntero
    auto copia() const { return [*this] { return n; }; }       // [17] captura una copia
};

int main() {
    int x = 1;
    auto por_valor = [x] { return x; };
    auto por_ref = [&x] { return x; };
    x = 10;
    assert(por_valor() == 1 && por_ref() == 10);

    // mutable: permite modificar la copia capturada
    auto acumulador = [total = 0](int v) mutable { return total += v; };
    acumulador(5);
    assert(acumulador(3) == 8);

    // init-capture [14]: mover un recurso dentro del cierre
    auto p = std::make_unique<std::string>("recurso");
    auto propietario = [q = std::move(p)] { return q->size(); };
    assert(p == nullptr && propietario() == 7);

    Contador c;
    auto inc = c.incrementador();
    inc();
    inc();
    auto foto = c.copia();
    c.n = 100;
    assert(foto() == 2);
}
