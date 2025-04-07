#include "dsc-miner/utils.hpp"

#include <cstdint>
#include <cstdlib>
#include <sys/fcntl.h>
#include <unistd.h>

namespace fs = std::filesystem;

bool write_file(const fs::path &path, const std::span<const uint8_t> buf) {
    const int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        return false;
    }
    const auto wrote_len = write(fd, buf.data(), buf.size_bytes());
    close(fd);
    return wrote_len == static_cast<ssize_t>(buf.size_bytes());
}
