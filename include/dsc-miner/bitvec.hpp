#pragma once

#undef NDEBUG
#include <cassert>

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

using elem_t = uint64_t;

class BitVec {
public:
    BitVec(size_t nbits) : m_nbits{nbits} {
        if (nbits % (sizeof(elem_t) * 8)) {
            abort();
        }
        buf = (elem_t *)calloc(1, size_bytes());
        if (!buf) {
            abort();
        }
    }

    ~BitVec() {
        free(buf);
    }

    size_t size() const {
        return m_nbits;
    }

    size_t size_bytes() const {
        return m_nbits / 8;
    }

    size_t size_elem() const {
        return size_bytes() / sizeof(elem_t);
    }

    size_t elem_idx(size_t bit_idx) const {
        return bit_idx / (sizeof(elem_t) * 8);
    }

    size_t elem_off(size_t bit_idx) const {
        return bit_idx % (sizeof(elem_t) * 8);
    }

    void set(size_t bit_idx) {
        buf[elem_idx(bit_idx)] |= 1ull << elem_off(bit_idx);
    }

    uint64_t popcnt() const {
        uint64_t cnt = 0;
        for (size_t i = 0; i < size_elem(); ++i) {
            cnt += std::popcount(buf[i]);
        }
        return cnt;
    }

private:
    const size_t m_nbits;
    elem_t *buf;
};
