#include <doctest/doctest.h>
#include "examples/embedded/frame_parser.hpp"
#include <array>

TEST_CASE("FrameParser extrae una trama válida ignorando ruido") {
    const std::array raw{std::byte{0x00}, std::byte{0xAA}, std::byte{2}, std::byte{7}, std::byte{8}};
    m04::FrameParser p;
    std::vector<std::vector<std::uint8_t>> frames;
    REQUIRE(p.feed(std::span{raw}, frames) == 1);
    CHECK(frames[0] == std::vector<std::uint8_t>{7, 8});
}
