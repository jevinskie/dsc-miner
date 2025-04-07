#pragma once

#include <cstdint>
#include <filesystem>
#include <span>
#include <type_traits>
#include <vector>

bool write_file(const std::filesystem::path &path, const std::span<const uint8_t> buf);

template <typename T> bool write_file(const std::filesystem::path &path, const std::span<T> buf) {
    return write_file(
        path, std::span{reinterpret_cast<const uint8_t *const>(buf.data()), buf.size_bytes()});
}

template <typename T>
bool write_file(const std::filesystem::path &path, const std::vector<T> &buf) {
    return write_file(path, std::span{reinterpret_cast<const uint8_t *const>(buf.data()),
                                      buf.size() * sizeof(T)});
}
