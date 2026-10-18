#pragma once
// Ronda 2 — versión corregida del código de la revisión. Cada cambio referencia el bug (Bn).
#include <bit>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <expected>
#include <limits>
#include <memory>
#include <mutex>
#include <span>
#include <string>
#include <vector>

struct MessageHeader {
    std::uint32_t type;
    std::uint32_t count;
};

class Message {
public:
    // B1-B4: propiedad por valor; Rule of Zero; origen copiado (sin string_view colgante)
    Message(std::string origin, std::span<const std::uint8_t> data)
        : origin_{std::move(origin)}, data_{data.begin(), data.end()} {}

    [[nodiscard]] const std::string& origin() const noexcept { return origin_; }
    [[nodiscard]] std::span<const std::uint8_t> data() const noexcept { return data_; }

private:
    std::string origin_;
    std::vector<std::uint8_t> data_;
};

class Handler {
public:
    virtual ~Handler() = default;   // B5
    virtual void on_message(const Message&) = 0;
};

class MessageQueue {
public:
    void push(Message m) {
        {
            std::lock_guard lock{mutex_};
            queue_.push_back(std::move(m));
        }
        cv_.notify_one();
    }

    Message pop() {   // B7: por valor
        std::unique_lock lock{mutex_};
        cv_.wait(lock, [this] { return !queue_.empty(); });   // B6: predicado
        Message m = std::move(queue_.front());
        queue_.pop_front();
        return m;
    }

    [[nodiscard]] std::size_t size() const {   // B8
        std::lock_guard lock{mutex_};
        return queue_.size();
    }

    void add_handler(std::unique_ptr<Handler> h) {   // B9: propiedad explícita y bajo lock
        std::lock_guard lock{mutex_};
        handlers_.push_back(std::move(h));
    }

    // B10: recorrido inverso correcto; se vacía la cola bajo lock y se despacha fuera
    // de él para que un handler pueda llamar a push() sin deadlock.
    void dispatch_all() {
        std::deque<Message> pendientes;
        std::vector<Handler*> hs;
        {
            std::lock_guard lock{mutex_};
            pendientes.swap(queue_);
            for (auto& h : handlers_) hs.push_back(h.get());
        }
        for (auto it = pendientes.rbegin(); it != pendientes.rend(); ++it) {
            for (Handler* h : hs) h->on_message(*it);
        }
    }

private:
    std::deque<Message> queue_;
    std::vector<std::unique_ptr<Handler>> handlers_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
};

enum class ParseError { Truncado, PayloadExcesivo, Desbordamiento };

// B11-B12: entrada no confiable. Validar antes de leer; aritmética comprobada.
inline std::expected<Message, ParseError> parse(std::span<const std::uint8_t> buf,
                                                const std::string& origin,
                                                std::size_t max_payload = 64 * 1024) {
    if (buf.size() < sizeof(MessageHeader)) return std::unexpected(ParseError::Truncado);
    MessageHeader hdr{};
    std::memcpy(&hdr, buf.data(), sizeof hdr);   // sin aliasing ni alineación
    if constexpr (sizeof(std::size_t) <= sizeof(std::uint32_t)) {
        // Solo con size_t de 32 bits (Cortex-M, ARMv7): count * 4 puede dar la vuelta
        if (hdr.count > std::numeric_limits<std::size_t>::max() / sizeof(std::uint32_t)) {
            return std::unexpected(ParseError::Desbordamiento);
        }
    }
    const std::size_t payload = std::size_t{hdr.count} * sizeof(std::uint32_t);
    if (payload > max_payload) return std::unexpected(ParseError::PayloadExcesivo);
    if (payload > buf.size() - sizeof(MessageHeader)) return std::unexpected(ParseError::Truncado);
    return Message{origin + ":" + std::to_string(hdr.type), buf.subspan(sizeof(MessageHeader), payload)};
}
