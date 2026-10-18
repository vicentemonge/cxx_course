// std::atomic, órdenes de memoria y wait/notify [11/20]
#include <atomic>
#include <cassert>
#include <thread>
#include <vector>

int main() {
    // Contador compartido: fetch_add relajado basta si solo importa el total
    std::atomic<int> contador{0};
    {
        std::vector<std::jthread> hilos;
        for (int i = 0; i < 4; ++i) {
            hilos.emplace_back([&] {
                for (int j = 0; j < 1000; ++j) contador.fetch_add(1, std::memory_order_relaxed);
            });
        }
    }
    assert(contador.load() == 4000);

    // Publicación con release/acquire: el dato es visible tras ver el flag
    int dato = 0;
    std::atomic<bool> listo{false};
    std::jthread productor{[&] { dato = 42; listo.store(true, std::memory_order_release); }};
    while (!listo.load(std::memory_order_acquire)) {}
    assert(dato == 42);

    // wait/notify [20]: bloquea sin espera activa hasta que el valor cambia
    std::atomic<int> fase{0};
    std::jthread esperador{[&] { fase.wait(0); assert(fase.load() == 1); }};
    fase.store(1);
    fase.notify_one();

    static_assert(std::atomic<int>::is_always_lock_free);   // [17]
}
