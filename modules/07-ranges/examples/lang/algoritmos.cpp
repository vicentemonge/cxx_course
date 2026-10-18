// Algoritmos añadidos entre C++11 y C++20
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);                    // [11] 1..10

    assert(std::all_of(v.begin(), v.end(), [](int x) { return x > 0; }));   // [11]
    assert(std::none_of(v.begin(), v.end(), [](int x) { return x > 10; }));

    auto [mn, mx] = std::minmax_element(v.begin(), v.end());                // [11]
    assert(*mn == 1 && *mx == 10);

    assert(std::clamp(15, 0, 10) == 10);                 // [17]
    assert(std::gcd(12, 18) == 6 && std::lcm(4, 6) == 12);   // [17]
    assert(std::reduce(v.begin(), v.end()) == 55);       // [17] reordenable/paralelizable

    assert(std::midpoint(2, 8) == 5);                    // [20] sin overflow
    assert(std::lerp(0.0, 10.0, 0.25) == 2.5);           // [20]

    std::vector<int> evens;
    std::copy_if(v.begin(), v.end(), std::back_inserter(evens), [](int x) { return x % 2 == 0; });
    assert(evens.size() == 5);

    std::shift_left(v.begin(), v.end(), 2);              // [20]
    assert(v[0] == 3);
}
