cmake_minimum_required(VERSION 3.31)

project(choma C)

set(CHOMA_SOURCES
    src/arm64.c
    src/Base64.c
    src/BufferedStream.c
    src/CodeDirectory.c
    src/CSBlob.c
    src/DER.c
    src/DyldSharedCache.c
    src/Entitlements.c
    src/Fat.c
    src/FileStream.c
    src/Host.c
    src/MachO.c
    src/MachOLoadCommand.c
    src/MemoryStream.c
    src/PatchFinder_arm64.c
    src/PatchFinder.c
    src/Util.c
)

set(CHOMA_HEADERS
    include/choma/arm64.h
    include/choma/Base64.h
    include/choma/BufferedStream.h
    include/choma/CachePatching.h
    include/choma/CodeDirectory.h
    include/choma/CSBlob.h
    include/choma/DER.h
    include/choma/dyld_cache_format.h
    include/choma/DyldSharedCache.h
    include/choma/Entitlements.h
    include/choma/Fat.h
    include/choma/FileStream.h
    include/choma/fixup-chains.h
    include/choma/Host.h
    include/choma/MachO.h
    include/choma/MachOByteOrder.h
    include/choma/MachOLoadCommand.h
    include/choma/MemoryStream.h
    include/choma/PatchFinder_arm64.h
    include/choma/PatchFinder.h
    include/choma/Util.h
)

# CHOMA_HEADERS added for IDE project generation
add_library(choma ${CHOMA_SOURCES} ${CHOMA_HEADERS})
target_include_directories(choma
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/choma
)

set_target_properties(choma PROPERTIES
    C_STANDARD 23
    C_EXTENSIONS ON
    C_STANDARD_REQUIRED ON
)
