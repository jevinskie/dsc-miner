#pragma once

#include <string>

#include <absl/container/flat_hash_map.h>

namespace dscm {
namespace detail {
static inline std::string block_str(double percentage, unsigned int width) {
    const auto full_width                    = width * 8;
    const unsigned int num_blk               = percentage * full_width;
    const auto full_blks                     = num_blk / 8;
    const auto partial_blks                  = num_blk % 8;
    static const std::string partial_chars[] = {"", "▏", "▎", "▍", "▌", "▋", "▊", "▉"};
    std::string res;
    for (unsigned int i = 0; i < full_blks; ++i) {
        res += "█";
    }
    return res + partial_chars[partial_blks];
}
} // namespace detail
} // namespace dscm

template <typename K, typename V> class Histogram {
public:
    V &operator[](const K &k) {
        auto [r, _] = m_h.try_emplace(k, 0);
        return r->second;
    }

    size_t size() const {
        return m_h.size();
    }

    auto begin() {
        return m_h.begin();
    }
    auto end() {
        return m_h.end();
    }
    auto cbegin() const {
        return m_h.cbegin();
    }
    auto cend() const {
        return m_h.cend();
    }

    std::string string(size_t top_n) const {
        std::string res;
        for (size_t i = 0; i < top_n; ++i) {
            res += dscm::detail::block_str((double)i / (top_n - 1), 80);
            res += "\n";
        }
        return res;
    }

private:
    absl::flat_hash_map<K, V> m_h;
};
