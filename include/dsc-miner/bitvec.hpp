#pragma once

#undef NDEBUG
#include <cassert>

#include <bit>
#include <cstddef>
#include <cstdint>
#include <vector>

using elem_t = uint64_t;

class BitVec {
public:
    BitVec(size_t nbits) : m_nbits{nbits}, m_buf(size_elem()) {
        if (nbits % size_one_elem_bits()) {
            abort();
        }
    }

    size_t size() const {
        return m_nbits;
    }

    size_t size_bytes() const {
        return m_nbits / 8;
    }

    size_t size_one_elem() const {
        return sizeof(elem_t);
    }

    size_t size_one_elem_bits() const {
        return size_one_elem() * 8;
    }

    size_t size_elem() const {
        return size_bytes() / size_one_elem();
    }

    size_t elem_idx(size_t bit_idx) const {
        return bit_idx / size_one_elem_bits();
    }

    size_t elem_off(size_t bit_idx) const {
        return bit_idx % size_one_elem_bits();
    }

    void set(size_t bit_idx) {
        m_buf[elem_idx(bit_idx)] |= 1ull << elem_off(bit_idx);
    }

    uint64_t popcnt() const {
        uint64_t cnt = 0;
        for (size_t i = 0; i < size_elem(); ++i) {
            cnt += std::popcount(m_buf[i]);
        }
        return cnt;
    }

private:
    const size_t m_nbits;
    std::vector<elem_t> m_buf;
};
