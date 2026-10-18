// std::async, future, promise y packaged_task [11]
#include <cassert>
#include <future>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

int main() {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);

    // async: lanzar trabajo y recoger el resultado
    auto mitad = v.begin() + 500;
    auto f1 = std::async(std::launch::async, [&] { return std::accumulate(v.begin(), mitad, 0L); });
    long resto = std::accumulate(mitad, v.end(), 0L);
    assert(f1.get() + resto == 500500);

    // promise: fijar el valor desde otro hilo
    std::promise<int> prom;
    auto fut = prom.get_future();
    std::jthread t{[&] { prom.set_value(7); }};
    assert(fut.get() == 7);

    // Las excepciones viajan a través del future
    auto fallo = std::async(std::launch::async, []() -> int { throw std::runtime_error("error"); });
    bool capturada = false;
    try { fallo.get(); } catch (const std::runtime_error&) { capturada = true; }
    assert(capturada);

    // packaged_task: envolver una función para ejecutarla más tarde
    std::packaged_task<int(int, int)> tarea{[](int a, int b) { return a * b; }};
    auto r = tarea.get_future();
    tarea(6, 7);
    assert(r.get() == 42);
}
