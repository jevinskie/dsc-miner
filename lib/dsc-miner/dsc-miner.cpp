#include <mach-o/loader.h>
#undef NDEBUG
#include <cassert>

#include "dsc-miner/dsc-miner.hpp"

#include <fmt/format.h>

extern "C" {
#include "choma/DyldSharedCache.h"
#include "choma/MachO.h"
}

namespace fs = std::filesystem;

void mine_dsc(const fs::path &dsc_path) {
    DyldSharedCache *dsc = dsc_init_from_path(dsc_path.c_str());
    assert(dsc);
    dsc_enumerate_files(dsc, ^(const char *fpath, size_t fsz, dyld_cache_header *hdr) {
        fmt::print("file: {:s} sz: {:d}\n", fpath, fsz);
    });
    dsc_enumerate_images(
        dsc, ^(const char *fpath, DyldSharedCacheImage *img_hndl, MachO *img_macho, bool *stop) {
            fmt::print("path: {:s}\n", fpath);
            const auto memstream = macho_get_stream(img_macho);
            assert(memstream);
            macho_enumerate_sections(
                img_macho, ^(section_64 *sect, segment_command_64 *seg, bool *stop) {
                    assert(!strncmp(sect->segname, seg->segname, sizeof(seg->segname)));
                    if (strncmp(seg->segname, "__TEXT", sizeof(seg->segname))) {
                        return;
                    }
                    if (strncmp(sect->sectname, "__text", sizeof(sect->sectname))) {
                        return;
                    }
                    fmt::print("text size: {:d}\n", sect->size);
                    assert(sect->size % 4 == 0);
                });
        });
    dsc_free(dsc);
}
