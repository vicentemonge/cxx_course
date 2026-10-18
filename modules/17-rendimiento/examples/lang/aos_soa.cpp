// AoS frente a SoA: misma operación, distinto uso de caché · @performance
#include <cassert>
#include <chrono>
#include <cstdio>
#include <numeric>
#include <vector>

struct ParticulaAoS {
    float x, y, z;
    float vx, vy, vz;
    float masa;
    int id;
};

struct ParticulasSoA {
    std::vector<float> x, y, z, vx, vy, vz, masa;
    std::vector<int> id;
};

template <typename F>
double medir_us(F&& f) {
    auto ini = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - ini).count();
}

int main() {
    constexpr std::size_t kN = 200'000;
    std::vector<ParticulaAoS> aos(kN);
    ParticulasSoA soa;
    soa.masa.resize(kN);
    for (std::size_t i = 0; i < kN; ++i) {
        aos[i].masa = static_cast<float>(i % 10);
        soa.masa[i] = aos[i].masa;
    }

    // Solo se usa la masa: AoS carga 32 bytes por elemento, SoA carga 4
    float total_aos = 0, total_soa = 0;
    double t_aos = medir_us([&] { for (const auto& p : aos) total_aos += p.masa; });
    double t_soa = medir_us([&] { total_soa = std::accumulate(soa.masa.begin(), soa.masa.end(), 0.0f); });

    assert(total_aos == total_soa);
    std::printf("AoS: %.0f us  SoA: %.0f us  (medir en Release; en Debug no es representativo)\n",
                t_aos, t_soa);
}
