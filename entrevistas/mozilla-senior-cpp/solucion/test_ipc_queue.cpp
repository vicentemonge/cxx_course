#include <doctest/doctest.h>
#include "ipc_queue.hpp"
#include <array>
#include <thread>

namespace {
std::vector<std::uint8_t> trama(std::uint32_t type, std::uint32_t count, std::size_t payload_real) {
    std::vector<std::uint8_t> b(sizeof(MessageHeader) + payload_real, 0xAB);
    MessageHeader h{type, count};
    std::memcpy(b.data(), &h, sizeof h);
    return b;
}

struct Contador : Handler {
    int* n;
    explicit Contador(int* p) : n{p} {}
    void on_message(const Message&) override { ++*n; }
};
} // namespace

TEST_CASE("parse rechaza entradas maliciosas") {
    CHECK(parse(std::span<const std::uint8_t>{}, "c").error() == ParseError::Truncado);
    auto mentirosa = trama(1, 1000, 8);   // declara 4000 bytes, envía 8
    CHECK(parse(mentirosa, "c").error() == ParseError::Truncado);
    auto enorme = trama(1, 0xFFFF'FFFFu, 0);
    CHECK_FALSE(parse(enorme, "c").has_value());
}

TEST_CASE("parse acepta una trama válida") {
    auto b = trama(7, 2, 8);
    auto m = parse(b, "contenido");
    REQUIRE(m);
    CHECK(m->origin() == "contenido:7");
    CHECK(m->data().size() == 8);
}

TEST_CASE("pop bloquea hasta que hay un mensaje") {
    MessageQueue q;
    std::jthread productor{[&] { q.push(Message{"p", {}}); }};
    Message m = q.pop();
    CHECK(m.origin() == "p");
}

TEST_CASE("dispatch_all entrega a todos los handlers y vacía la cola") {
    MessageQueue q;
    int n = 0;
    q.add_handler(std::make_unique<Contador>(&n));
    q.add_handler(std::make_unique<Contador>(&n));
    q.push(Message{"a", {}});
    q.push(Message{"b", {}});
    q.dispatch_all();
    CHECK(n == 4);
    CHECK(q.size() == 0);
    q.dispatch_all();   // con la cola vacía no hay bucle infinito
}
