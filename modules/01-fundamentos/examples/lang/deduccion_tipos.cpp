// auto, decltype, decltype(auto), trailing return y trampas [11/14/17]
#include <cassert>
#include <type_traits>
#include <vector>

int global = 0;
int& ref_global() { return global; }

auto f_auto() { return ref_global(); }            // auto decae: devuelve int
decltype(auto) f_dauto() { return ref_global(); } // conserva la referencia: int&

template <typename A, typename B>
auto suma(A a, B b) -> decltype(a + b) { return a + b; }  // trailing return [11]

int main() {
    static_assert(std::is_same_v<decltype(f_auto()), int>);
    static_assert(std::is_same_v<decltype(f_dauto()), int&>);
    f_dauto() = 5;
    assert(global == 5);

    static_assert(std::is_same_v<decltype(suma(1, 2.0)), double>);

    // auto con llaves: desde C++17 "auto x{1}" es int, "auto y = {1}" es initializer_list
    auto x{1};
    auto y = {1, 2};
    static_assert(std::is_same_v<decltype(x), int>);
    static_assert(std::is_same_v<decltype(y), std::initializer_list<int>>);

    // decltype de un nombre vs de una expresión
    int v = 0;
    static_assert(std::is_same_v<decltype(v), int>);
    static_assert(std::is_same_v<decltype((v)), int&>);

    // Trampa: vector<bool> devuelve un proxy, no bool&
    std::vector<bool> flags{true, false};
    auto bit = flags[0];
    static_assert(!std::is_same_v<decltype(bit), bool>);
    bit = false;               // modifica el vector a través del proxy
    assert(flags[0] == false);
}
