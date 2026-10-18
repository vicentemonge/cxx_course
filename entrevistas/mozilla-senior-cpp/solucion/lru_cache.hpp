#pragma once
// Ronda 1 — LRU cache genérico. Solución de referencia con los seguimientos resueltos.
#include <cassert>
#include <cstddef>
#include <functional>
#include <list>
#include <mutex>
#include <optional>
#include <unordered_map>
#include <utility>

template <class K, class V, class Hash = std::hash<K>, class Eq = std::equal_to<K>>
class LruCache {
public:
    explicit LruCache(std::size_t capacidad) : cap_{capacidad} {
        assert(cap_ > 0);
        index_.reserve(cap_);   // sin rehash en el camino caliente
    }

    // Devuelve un puntero estable hasta el siguiente put/erase. Un get modifica el orden:
    // no es una operación de solo lectura (clave para el seguimiento de concurrencia).
    V* get(const K& k) {
        auto it = index_.find(k);
        if (it == index_.end()) return nullptr;
        items_.splice(items_.begin(), items_, it->second);   // O(1), sin asignaciones
        return &it->second->second;
    }

    void put(K k, V v) {
        if (auto it = index_.find(k); it != index_.end()) {
            it->second->second = std::move(v);
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        if (items_.size() == cap_) {
            // Lleno: reutilizar el nodo menos usado (ni list ni map asignan memoria).
            auto ultimo = std::prev(items_.end());
            auto nodo = index_.extract(ultimo->first);       // node handle [17]
            nodo.key() = k;
            ultimo->first = std::move(k);
            ultimo->second = std::move(v);
            items_.splice(items_.begin(), items_, ultimo);
            index_.insert(std::move(nodo));
            return;
        }
        // Garantía fuerte: si falla la inserción en el índice, se deshace la de la lista.
        items_.emplace_front(std::move(k), std::move(v));
        try {
            index_.emplace(items_.front().first, items_.begin());
        } catch (...) {
            items_.pop_front();
            throw;
        }
    }

    [[nodiscard]] std::size_t size() const noexcept { return items_.size(); }

private:
    using Lista = std::list<std::pair<K, V>>;
    std::size_t cap_;
    Lista items_;   // frente = más reciente
    std::unordered_map<K, typename Lista::iterator, Hash, Eq> index_;
};

// Seguimiento: versión concurrente. get() muta el orden, así que un shared_mutex no ayuda:
// todo acceso necesita exclusión. Se devuelve una copia porque el puntero no sobrevive al lock.
template <class K, class V>
class LruCacheConcurrente {
public:
    explicit LruCacheConcurrente(std::size_t cap) : cache_{cap} {}
    std::optional<V> get(const K& k) {
        std::scoped_lock lk{m_};
        if (V* v = cache_.get(k)) return *v;
        return std::nullopt;
    }
    void put(K k, V v) {
        std::scoped_lock lk{m_};
        cache_.put(std::move(k), std::move(v));
    }

private:
    std::mutex m_;
    LruCache<K, V> cache_;
};
