#undef NDEBUG
#include <cassert>

#include "dsc-miner/dsc-miner.hpp"

#include <fmt/format.h>

extern "C" {
#include "choma/DyldSharedCache.h"
}

namespace fs = std::filesystem;

void mine_dsc(const fs::path &dsc_path) {
    DyldSharedCache *dsc = dsc_init_from_path(dsc_path.c_str());
    assert(dsc);
    dsc_enumerate_files(dsc, ^(const char *fpath, size_t fsz, dyld_cache_header *hdr) {
        fmt::print("file: {:s} sz: {:d}\n", fpath, fsz);
    });
    dsc_enumerate_images(dsc, ^(const char *fpath, DyldSharedCacheImage *img_hndl, MachO *img_macho,
                                bool *stop) { fmt::print("path: {:s}\n", fpath); });
    dsc_free(dsc);
}
