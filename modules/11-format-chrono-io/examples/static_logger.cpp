#include "examples/static_logger.hpp"
#include <cstdio>

int main() {
    m11::StaticLogger<64> log;
    auto line = log.log("[{:>6}] {}", 1234, m11::Telemetry{235, 3712});
    std::printf("%.*s\n", static_cast<int>(line.size()), line.data());
}
