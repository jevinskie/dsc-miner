#undef NDEBUG
#include <cassert>

#include "dsc-miner/dsc-miner.hpp"

#include "dsc-miner/bitvec.hpp"
#include "dsc-miner/histogram.hpp"
#include "dsc-miner/utils.hpp"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

#include <binja-arm64dis/arm64dis.h>
#include <fmt/format.h>

extern "C" {
#include "choma/DyldSharedCache.h"
#include "choma/MachO.h"
}

namespace fs = std::filesystem;

void mine_dsc(const fs::path &dsc_path) {
    DyldSharedCache *dsc = dsc_init_from_path(dsc_path.c_str());
    assert(dsc);
    __block size_t total_sz = 0;
    __block BitVec bv{0x1'0000'0000ull};
    __block Histogram<uint32_t, uint32_t> hist;
    dsc_enumerate_images(
        dsc, ^(const char *fpath, DyldSharedCacheImage *img_hndl, MachO *img_macho, bool *stop) {
            macho_enumerate_sections(
                img_macho, ^(section_64 *sect, segment_command_64 *seg, bool *stop) {
                    assert(!strncmp(sect->segname, seg->segname, sizeof(seg->segname)));
                    if (strncmp(seg->segname, "__TEXT", sizeof(seg->segname))) {
                        return;
                    }
                    if (strncmp(sect->sectname, "__text", sizeof(sect->sectname))) {
                        return;
                    }
                    assert(sect->size % sizeof(uint32_t) == 0);
                    if (!sect->size) {
                        return;
                    }
                    const size_t num_words    = sect->size / sizeof(uint32_t);
                    const uint64_t base       = macho_get_base_address(img_macho);
                    const uint64_t txt_vmaddr = sect->addr;
                    assert(sect->addr >= base);
                    const uint64_t txt_off = sect->addr - base;
                    const auto memstream   = macho_get_stream(img_macho);
                    assert(memstream);
                    const uint8_t *const mhb  = memory_stream_get_raw_pointer(memstream);
                    const uint32_t *const txt = (uint32_t *)(mhb + txt_off);
                    for (size_t i = 0; i < num_words; ++i) {
                        const auto inst = txt[i];
                        bv.set(inst);
                        ++hist[inst];
                    }
                    total_sz += sect->size;
                });
        });
    const auto total_words = total_sz / sizeof(uint32_t);
    fmt::print("total_sz: {:d} num instrs: {:d}\n", total_sz, total_words);
    const auto num_unique   = bv.popcnt();
    const auto percent_used = ((double)num_unique / (double)0x1'0000'0000ull) * 100.0;
    fmt::print("bitvec popcount: {:d} % used: {:.3g} # instr / # unique: {:.3g}\n", num_unique,
               percent_used, (double)total_words / num_unique);
    // fmt::print("hist:\n{:s}\n", hist.string(8));
    fmt::print("hist size: {:d}\n", hist.size());

    std::vector<std::pair<uint32_t, uint32_t>> instr_counts;
    std::copy(hist.cbegin(), hist.cend(), std::back_inserter(instr_counts));
    std::sort(instr_counts.begin(), instr_counts.end(), [](const auto a, const auto b) {
        return a.second < b.second;
    });
    std::reverse(instr_counts.begin(), instr_counts.end());
    std::vector<uint32_t> instr_counts_flat;
    std::vector<uint32_t> instr_counts_instrs;
    instr_counts_flat.reserve(hist.size() * 2);
    instr_counts_instrs.reserve(hist.size());
    std::for_each(instr_counts.cbegin(), instr_counts.cend(), [&](const auto &p) {
        instr_counts_flat.push_back(p.first);
        instr_counts_flat.push_back(p.second);
        instr_counts_instrs.push_back(p.first);
    });
    // write_file("instr-counts.bin", instr_counts_flat);
    // write_file("unique-instrs-sorted-by-frequency.bin", instr_counts_instrs);
    const size_t num_instr_print = std::min(instr_counts_instrs.size(), (size_t)32);
    for (size_t i = 0; i < num_instr_print; ++i) {
        char dis_buf[1024];
        const auto inst_word = instr_counts_instrs[i];
        Instruction inst;
        const auto res_decomp = aarch64_decompose(inst_word, &inst, 0);
        if (res_decomp) {
            fmt::print("top[{:d}]: {:08x} aarch64_decompose failed {:d}\n", i, inst_word,
                       res_decomp);
            continue;
        }
        const int res_dis = aarch64_disassemble(&inst, dis_buf, sizeof(dis_buf));
        if (!res_dis) {
            fmt::print("top[{:d}]: {:08x} {:s}\n", i, inst_word, dis_buf);
        } else {
            fmt::print("top[{:d}]: {:08x} aarch64_disassemble failed {:d}\n", i, inst_word,
                       res_dis);
        }
    }
    return;

    std::vector<uint32_t> unique_instrs;
    unique_instrs.reserve(hist.size());
    std::transform(hist.cbegin(), hist.cend(), std::back_inserter(unique_instrs),
                   [](const auto &p) {
                       return p.first;
                   });
    write_file("unique-instrs.bin", unique_instrs);
    std::sort(unique_instrs.begin(), unique_instrs.end());
    write_file("unique-instrs-sorted.bin", unique_instrs);
    std::for_each(unique_instrs.begin(), unique_instrs.end(), [](uint32_t &v) {
        v = std::byteswap(v);
    });
    std::sort(unique_instrs.begin(), unique_instrs.end());
    write_file("unique-instrs-sorted-bswap.bin", unique_instrs);
    std::for_each(unique_instrs.begin(), unique_instrs.end(), [](uint32_t &v) {
        v = __builtin_bitreverse32(std::byteswap(v));
    });
    std::sort(unique_instrs.begin(), unique_instrs.end());
    write_file("unique-instrs-sorted-brev.bin", unique_instrs);
    std::for_each(unique_instrs.begin(), unique_instrs.end(), [](uint32_t &v) {
        v = std::byteswap(v);
    });
    std::sort(unique_instrs.begin(), unique_instrs.end());
    write_file("unique-instrs-sorted-brev-bswap.bin", unique_instrs);
}
