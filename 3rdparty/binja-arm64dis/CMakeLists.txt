cmake_minimum_required(VERSION 3.31)

project(binja-arm64dis C)

set(BINJA_ARM64DIS_DECODE_SOURCES
    src/decode.c
    src/decode0.c
    src/decode1.c
    src/decode2.c
    src/decode_fields32.c
    src/decode_scratchpad.c
    src/encodings_dec.c
    src/pcode.c
)

set(BINJA_ARM64DIS_DECODE_HEADERS
    include/binja-arm64dis/decode.h
    include/binja-arm64dis/decode1.h
    include/binja-arm64dis/decode2.h
    include/binja-arm64dis/decode_fields32.h
    include/binja-arm64dis/encodings_dec.h
    include/binja-arm64dis/pcode.h
)

# BINJA_ARM64DIS_DECODE_HEADERS added for IDE project generation
add_library(binja-arm64dis-decode ${BINJA_ARM64DIS_DECODE_SOURCES} ${BINJA_ARM64DIS_DECODE_HEADERS})
target_include_directories(binja-arm64dis-decode
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/binja-arm64dis
)

set_target_properties(binja-arm64dis-decode PROPERTIES
    C_STANDARD 23
    C_EXTENSIONS ON
    C_STANDARD_REQUIRED ON
)

set(BINJA_ARM64DIS_FORMAT_SOURCES
    src/format.c
    src/encodings_fmt.c
    src/operations.c
    src/regs.c
    src/sysregs.c
)

set(BINJA_ARM64DIS_FORMAT_HEADERS
    include/binja-arm64dis/format.h
    include/binja-arm64dis/encodings_fmt.h
    include/binja-arm64dis/operations.h
    include/binja-arm64dis/regs.h
    include/binja-arm64dis/sysregs.h
)

add_library(binja-arm64dis-format ${BINJA_ARM64DIS_FORMAT_SOURCES} ${BINJA_ARM64DIS_FORMAT_HEADERS})
target_include_directories(binja-arm64dis-format
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/binja-arm64dis
)
target_link_libraries(binja-arm64dis-format PRIVATE binja-arm64dis-decode)

set_target_properties(binja-arm64dis-format PROPERTIES
    C_STANDARD 23
    C_EXTENSIONS ON
    C_STANDARD_REQUIRED ON
)

add_library(binja-arm64dis INTERFACE)
target_include_directories(binja-arm64dis INTERFACE include)
target_link_libraries(binja-arm64dis INTERFACE binja-arm64dis-decode binja-arm64dis-format)
