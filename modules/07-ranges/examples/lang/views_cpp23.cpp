// Views y utilidades de C++23: zip, enumerate, chunk, slide, to, fold_left
#include <cassert>
#include <cstdio>
#include <ranges>
#include <string>
#include <vector>
#if defined(__cpp_lib_ranges_fold)
#include <algorithm>
#endif

int main() {
    std::vector<std::string> nombres{"a", "b", "c"};
    std::vector<int> valores{1, 2, 3};

#if defined(__cpp_lib_ranges_zip)
    for (auto [n, v] : std::views::zip(nombres, valores)) std::printf("%s=%d ", n.c_str(), v);
    std::printf("\n");
#endif
#if defined(__cpp_lib_ranges_enumerate)
    for (auto [i, n] : std::views::enumerate(nombres)) assert(nombres[static_cast<std::size_t>(i)] == n);
#endif
#if defined(__cpp_lib_ranges_chunk)
    std::vector<int> datos{1, 2, 3, 4, 5};
    int bloques = 0;
    for (auto bloque : datos | std::views::chunk(2)) { ++bloques; (void)bloque; }
    assert(bloques == 3);
#endif
#if defined(__cpp_lib_ranges_slide)
    auto ventanas = valores | std::views::slide(2);   // {1,2}, {2,3}
    assert(std::ranges::distance(ventanas) == 2);
#endif
#if defined(__cpp_lib_ranges_to_container)
    auto pares = std::views::iota(0, 10)
               | std::views::filter([](int x) { return x % 2 == 0; })
               | std::ranges::to<std::vector>();
    assert(pares.size() == 5);
#endif
#if defined(__cpp_lib_ranges_fold)
    assert(std::ranges::fold_left(valores, 0, std::plus<>{}) == 6);
#endif
}
