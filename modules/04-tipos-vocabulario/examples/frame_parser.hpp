#pragma once
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <variant>
#include <vector>

namespace m04 {

// Trama: 0xAA | len | payload[len]
struct WaitSync {};
struct WaitLen {};
struct ReadPayload {
    std::uint8_t len;
    std::vector<std::uint8_t> data;
};
using State = std::variant<WaitSync, WaitLen, ReadPayload>;

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

class FrameParser {
public:
    std::optional<std::vector<std::uint8_t>> feed(std::uint8_t b) {
        std::optional<std::vector<std::uint8_t>> out;
        state_ = std::visit(overloaded{
            [&](WaitSync) -> State { return b == 0xAA ? State{WaitLen{}} : State{WaitSync{}}; },
            [&](WaitLen) -> State { return ReadPayload{b, {}}; },
            [&](ReadPayload& p) -> State {
                p.data.push_back(b);
                if (p.data.size() == p.len) { out = std::move(p.data); return WaitSync{}; }
                return std::move(p);
            }}, state_);
        return out;
    }

    std::size_t feed(std::span<const std::byte> bytes,
                     std::vector<std::vector<std::uint8_t>>& frames) {
        for (auto b : bytes) {
            if (auto f = feed(std::to_integer<std::uint8_t>(b))) frames.push_back(std::move(*f));
        }
        return frames.size();
    }

private:
    State state_{WaitSync{}};
};

} // namespace m04
