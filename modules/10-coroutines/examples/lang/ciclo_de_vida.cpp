// Ciclo de vida de una coroutine: qué llama el compilador y cuándo [20]
#include <coroutine>
#include <cstdio>
#include <exception>
#include <string>
#include <vector>

std::vector<std::string> trazas;

struct Tarea {
    struct promise_type {
        promise_type() { trazas.emplace_back("promise()"); }
        Tarea get_return_object() {
            trazas.emplace_back("get_return_object");
            return Tarea{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { trazas.emplace_back("initial_suspend"); return {}; }
        std::suspend_always final_suspend() noexcept { trazas.emplace_back("final_suspend"); return {}; }
        void return_void() { trazas.emplace_back("return_void"); }
        void unhandled_exception() { std::terminate(); }
    };

    explicit Tarea(std::coroutine_handle<promise_type> h) : h_{h} {}
    Tarea(const Tarea&) = delete;
    Tarea& operator=(const Tarea&) = delete;
    ~Tarea() { if (h_) h_.destroy(); }
    void reanudar() { h_.resume(); }

private:
    std::coroutine_handle<promise_type> h_;
};

// Awaiter mínimo: decide si suspender y qué devolver al reanudar
struct Pausa {
    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<>) const noexcept { trazas.emplace_back("await_suspend"); }
    void await_resume() const noexcept { trazas.emplace_back("await_resume"); }
};

Tarea corrutina() {
    trazas.emplace_back("cuerpo: inicio");
    co_await Pausa{};
    trazas.emplace_back("cuerpo: fin");
}

int main() {
    Tarea t = corrutina();       // se crea el frame y se suspende en initial_suspend
    trazas.emplace_back("main: resume 1");
    t.reanudar();                // ejecuta hasta co_await
    trazas.emplace_back("main: resume 2");
    t.reanudar();                // termina y se suspende en final_suspend
    for (const auto& s : trazas) std::printf("%s\n", s.c_str());
    return trazas.back() == "final_suspend" ? 0 : 1;
}
