// std::jthread y cancelación cooperativa con stop_token [20]
#include <atomic>
#include <cassert>
#include <chrono>
#include <thread>

int main() {
    std::atomic<int> vueltas{0};
    {
        std::jthread trabajador{[&](std::stop_token st) {
            while (!st.stop_requested()) {
                ++vueltas;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }};
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }   // el destructor de jthread pide parada y hace join: sin std::terminate
    assert(vueltas > 0);

    // stop_callback: ejecuta código cuando se solicita la parada
    std::stop_source fuente;
    bool notificado = false;
    std::stop_callback cb{fuente.get_token(), [&] { notificado = true; }};
    fuente.request_stop();
    assert(notificado);
}
