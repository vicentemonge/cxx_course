// std::pmr: contenedores estándar sobre un buffer fijo, sin heap [17]
#include <array>
#include <cassert>
#include <cstddef>
#include <memory_resource>
#include <vector>

int main() {
    std::array<std::byte, 1024> buffer{};
    // Asignador monotónico: reparte memoria del buffer y no libera hasta destruirse.
    // null_memory_resource como respaldo: si se agota, lanza bad_alloc en vez de usar heap.
    std::pmr::monotonic_buffer_resource pool{buffer.data(), buffer.size(),
                                             std::pmr::null_memory_resource()};

    std::pmr::vector<int> v{&pool};
    v.reserve(16);
    for (int i = 0; i < 16; ++i) v.push_back(i);
    assert(v.size() == 16);

    // Los datos viven dentro del buffer
    auto* ini = reinterpret_cast<std::byte*>(v.data());
    assert(ini >= buffer.data() && ini < buffer.data() + buffer.size());

    bool agotado = false;
    try {
        std::pmr::vector<int> grande{&pool};
        grande.reserve(10'000);
    } catch (const std::bad_alloc&) {
        agotado = true;
    }
    assert(agotado);
}
