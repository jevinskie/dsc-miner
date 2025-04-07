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

add_library(choma ${CHOMA_SOURCES})
target_include_directories(choma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(choma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/choma)
set_target_properties(choma PROPERTIES
    C_STANDARD 23
    C_EXTENSIONS ON
    C_STANDARD_REQUIRED ON
)
