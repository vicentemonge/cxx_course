// Contar asignaciones: reserve, SSO y pmr · @performance @lifetime
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <memory_resource>
#include <new>
#include <string>
#include <vector>

static std::size_t g_asignaciones = 0;

void* operator new(std::size_t n) {
    ++g_asignaciones;
    if (void* p = std::malloc(n)) return p;
    throw std::bad_alloc{};
}
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

template <typename F>
std::size_t contar(F&& f) {
    auto antes = g_asignaciones;
    f();
    return g_asignaciones - antes;
}

int main() {
    auto sin_reserve = contar([] { std::vector<int> v; for (int i = 0; i < 1000; ++i) v.push_back(i); });
    auto con_reserve = contar([] { std::vector<int> v; v.reserve(1000); for (int i = 0; i < 1000; ++i) v.push_back(i); });
    assert(con_reserve == 1 && sin_reserve > 1);

    auto corta = contar([] { std::string s = "corta"; (void)s; });                    // SSO
    auto larga = contar([] { std::string s(100, 'x'); (void)s; });
    assert(corta == 0 && larga == 1);

    auto con_pmr = contar([] {
        std::byte buf[8192];
        std::pmr::monotonic_buffer_resource mr{buf, sizeof buf, std::pmr::null_memory_resource()};
        std::pmr::vector<int> v{&mr};
        for (int i = 0; i < 1000; ++i) v.push_back(i);
    });
    assert(con_pmr == 0);

    std::printf("push_back sin reserve: %zu asignaciones, con reserve: %zu, pmr: %zu\n",
                sin_reserve, con_reserve, con_pmr);
}
