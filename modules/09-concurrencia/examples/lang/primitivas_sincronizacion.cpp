// mutex, scoped_lock, latch, barrier y semáforos [11/17/20]
#include <barrier>
#include <cassert>
#include <latch>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>

int main() {
    // scoped_lock [17]: bloquea varios mutex sin riesgo de deadlock
    std::mutex m1, m2;
    int a = 0, b = 0;
    auto transferir = [&] { std::scoped_lock lk{m1, m2}; ++a; --b; };

    // latch [20]: espera de un solo uso hasta que N hilos terminan
    constexpr int kHilos = 4;
    std::latch listos{kHilos};
    std::vector<std::jthread> hilos;
    for (int i = 0; i < kHilos; ++i) {
        hilos.emplace_back([&] { transferir(); listos.count_down(); });
    }
    listos.wait();
    assert(a == kHilos && b == -kHilos);
    hilos.clear();

    // barrier [20]: punto de encuentro reutilizable por fases
    int fases = 0;
    std::barrier sync{kHilos, [&]() noexcept { ++fases; }};
    for (int i = 0; i < kHilos; ++i) {
        hilos.emplace_back([&] { for (int f = 0; f < 3; ++f) sync.arrive_and_wait(); });
    }
    hilos.clear();
    assert(fases == 3);

    // counting_semaphore [20]: limitar el acceso concurrente a un recurso
    std::counting_semaphore<2> plazas{2};
    plazas.acquire();
    assert(plazas.try_acquire());
    assert(!plazas.try_acquire());
    plazas.release(2);
}
