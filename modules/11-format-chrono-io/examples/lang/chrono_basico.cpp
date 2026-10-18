// <chrono>: duraciones, literales y calendario [11/14/20]
#include <cassert>
#include <chrono>
#include <cstdio>

int main() {
    using namespace std::chrono_literals;   // [14]
    using namespace std::chrono;

    auto t = 1h + 30min + 15s;
    assert(duration_cast<minutes>(t).count() == 90);       // trunca
    static_assert(seconds{90} == 1min + 30s);

    milliseconds ms = 2s;                   // conversión implícita sin pérdida
    // seconds s = 1500ms;                  // error: perdería precisión
    assert(ms.count() == 2000);
    assert(round<seconds>(1500ms) == 2s);

    // Medir tiempo
    auto ini = steady_clock::now();
    auto fin = steady_clock::now();
    assert(fin >= ini);

    // Calendario [20]
    constexpr year_month_day fecha{2024y / February / 29};
    static_assert(fecha.ok());
    static_assert(!year_month_day{2023y / February / 29}.ok());
    constexpr auto siguiente = sys_days{fecha} + days{1};
    static_assert(year_month_day{siguiente} == 2024y / March / 1);
    constexpr weekday wd{sys_days{fecha}};
    static_assert(wd == Thursday);
    std::printf("2024-02-29 fue jueves\n");
}
