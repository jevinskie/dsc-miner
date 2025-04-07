#include "dsc-miner/dsc-miner.hpp"
#include <fmt/format.h>

int main(int argc, const char **argv) {
    if (argc != 2) {
        fmt::print("usage: dsc-miner-util <path to dsc>\n");
        return 1;
    }
    fmt::print("hello world\n");
    mine_dsc(argv[1]);
    return 0;
}
