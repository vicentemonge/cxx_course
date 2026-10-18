#include "examples/embedded/frame_parser.hpp"
#include <array>
#include <cstdio>

int main() {
    const std::array raw{std::byte{0xAA}, std::byte{2}, std::byte{0x10}, std::byte{0x20}};
    m04::FrameParser p;
    std::vector<std::vector<std::uint8_t>> frames;
    p.feed(std::as_bytes(std::span{raw}), frames);
    std::printf("tramas: %zu\n", frames.size());
}
