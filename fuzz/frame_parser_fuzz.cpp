// Fuzzer del parser de tramas del módulo 04 (ejercicio del módulo 18).
#include "examples/embedded/frame_parser.hpp"
#include <cstddef>
#include <cstdint>
#include <span>

extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t* data, std::size_t size) {
    m04::FrameParser parser;
    std::vector<std::vector<std::uint8_t>> frames;
    parser.feed(std::as_bytes(std::span{data, size}), frames);
    for (const auto& f : frames) {
        if (f.empty() || f.size() > 255) __builtin_trap();   // invariante: 1..255 bytes de payload
    }
    return 0;
}
