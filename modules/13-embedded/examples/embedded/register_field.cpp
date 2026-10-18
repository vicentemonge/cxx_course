#include "examples/embedded/register_field.hpp"
#include <cinttypes>
#include <cstdio>

int main() {
    std::uint32_t cr1 = 0;
    cr1 = m13::UE::insert(cr1, 1);
    cr1 = m13::PCE::insert(cr1, 1);
    std::printf("CR1=0x%08" PRIX32 " UE=%" PRIu32 "\n", cr1, m13::UE::extract(cr1));
}
